#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <time.h>
#include <signal.h>

#define _GNU_SOURCE
#define BUFF 4096
#define MAX_PRELOADED 5120

char *preloaded_paths[MAX_PRELOADED];
int preload_count = 0;
time_t last_seen_time = 0;

void NFC(const char *message) {
    char cmd[BUFF];
    snprintf(cmd, sizeof(cmd),
             "cmd notification post -S bigtext -t '♨️ Perload Esport' 'tag' '%s' > /dev/null 2>&1", message);
    system(cmd);
}

int already_preloaded(const char *path) {
    for (int i = 0; i < preload_count; i++) {
        if (strcmp(preloaded_paths[i], path) == 0)
            return 1;
    }
    return 0;
}

void mark_preloaded(const char *path) {
    if (preload_count < MAX_PRELOADED) {
        preloaded_paths[preload_count++] = strdup(path);
    }
}

void preload_file(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return;

    struct stat st;
    if (fstat(fd, &st) != 0 || st.st_size == 0) {
        close(fd);
        return;
    }

    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        return;
    }

    madvise(map, st.st_size, MADV_WILLNEED);
    mlock(map, st.st_size);

    while (1) sleep(5);

    munmap(map, st.st_size);
    close(fd);
}

void kill_preload_game(const char *pkg) {
    FILE *pid_fp = fopen("/sdcard/Esport/high.8", "r");
    if (!pid_fp) return;

    int pid;
    while (fscanf(pid_fp, "%d", &pid) == 1) {
        kill(pid, SIGKILL);
    }
    fclose(pid_fp);
    remove("/sdcard/Esport/high.8");
}

void kill_preload_low() {
    FILE *pid_fp = fopen("/sdcard/Esport/low.8", "r");
    if (!pid_fp) return;

    int pid;
    while (fscanf(pid_fp, "%d", &pid) == 1) {
        kill(pid, SIGKILL);
    }

    fclose(pid_fp);
    remove("/sdcard/Esport/low.8");
}

void spawn_preloader(const char *file, int is_game) {
    pid_t pid = fork();
    if (pid == 0) {
        setsid();
        int null_fd = open("/dev/null", O_RDWR);
        if (null_fd >= 0) {
            dup2(null_fd, 0);
            dup2(null_fd, 1);
            dup2(null_fd, 2);
            if (null_fd > 2) close(null_fd);
        }

        char exe_path[BUFF];
        ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
        if (len == -1) _exit(1);
        exe_path[len] = '\0';

        char *args[] = { exe_path, "-dL", (char *)file, NULL };
        execvp(exe_path, args);
        _exit(1);
    } else if (pid > 0) {
        const char *pid_file = is_game ? "/sdcard/Esport/high.8" : "/sdcard/Esport/low.8";
        FILE *pid_fp = fopen(pid_file, "a");
        if (pid_fp) {
            fprintf(pid_fp, "%d\n", pid);
            fclose(pid_fp);
        }
    }
}

void preload_from_ls(const char *cmd, int is_game) {
    FILE *fp = popen(cmd, "r");
    if (!fp) return;

    char path[BUFF];
    while (fgets(path, sizeof(path), fp)) {
        path[strcspn(path, "\r\n")] = 0;
        if (path[0] != '\0' && !already_preloaded(path)) {
            spawn_preloader(path, is_game);
            mark_preloaded(path);
        }
    }

    pclose(fp);
}

int check_app_running(const char *app_name) {
    char command[BUFF];
    snprintf(command, sizeof(command),
             "dumpsys SurfaceFlinger | grep Output | head -n 1 | cut -f1 -d/ | awk -F '(' '{print $2}' | grep -w \"%s\"", app_name);
    FILE *fp = popen(command, "r");
    if (!fp) return 0;

    char buffer[BUFF];
    int found = fgets(buffer, sizeof(buffer), fp) != NULL;
    pclose(fp);
    return found;
}

void preload_high(const char *pkg) {
    preload_from_ls("find /system/vendor/lib64/ -type f | grep -Ei 'exynos|mali|vulkan|flinger|policy|skia|hwui|composer|gralloc|egl|memory|cache|cpu|android'", 1);
    preload_from_ls("cmd package path android | cut -f2 -d:", 1);
    preload_from_ls("cmd package path com.android.systemui | cut -f2 -d:", 1);
    system("cmd activity memory-factor set CRITICAL ");
    char cmd[BUFF];
    snprintf(cmd, sizeof(cmd), "cmd package path %s | cut -f2 -d:", pkg);
    preload_from_ls(cmd, 1);
    snprintf(cmd, sizeof(cmd), "find /sdcard/Android/data/%s/cache -type d ", pkg);
    preload_from_ls(cmd, 1);
}

void preload_low() {
    preload_from_ls("cmd package path android | cut -f2 -d:", 0);
    preload_from_ls("cmd package path com.android.systemui | cut -f2 -d:", 0);
    preload_from_ls("find /system/lib/ -type f | grep -Ei 'hwui|egl|open'", 0);
    preload_from_ls("find /vendor/lib/ -type f | grep -Ei 'egl|meow'", 0);
    system("cmd activity memory-factor set NORMAL ");
}

int main(int argc, char *argv[]) {
    if (argc >= 3 && strcmp(argv[1], "-dL") == 0) {
        preload_file(argv[2]);
        return 0;
    }

    NFC("♨️ Perload Esport Priority is running in background");
    sleep(1);
    NFC("♨️ Perload Esport Priority game: By @UnixeID");

    const char *primary_path = "/sdcard/Esport/Gamelist.txt";
    char line[BUFF];
    char app_running[BUFF] = "";

    while (1) {
        FILE *file = fopen(primary_path, "r");
        if (!file) {
            static int err = 0;
            if (err++ % 10 == 0)
                printf("Gamelist tidak ditemukan!\n");
            sleep(1);
            continue;
        }

        int found = 0;
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = '\0';
            if (check_app_running(line)) {
                found = 1;
                time(&last_seen_time);

                if (strcmp(line, app_running) != 0) {
                    char message[BUFF];
                    snprintf(message, sizeof(message), "[ Perload in Game : %s ]", line);
                    NFC(message);
                    strcpy(app_running, line);

                    kill_preload_low();     // Tambahan penting
                    preload_count = 0;
                    preload_high(line);
                }
                break;
            }
        }
        fclose(file);

        time_t now;
        time(&now);

        if (!found && strlen(app_running) > 0) {
            double seconds_inactive = difftime(now, last_seen_time);
            if (seconds_inactive >= 180) {
                NFC("[Perload sistem: game close ]");
                kill_preload_game(app_running);
                strcpy(app_running, "");

                preload_count = 0;
                preload_low();
            }
        }

        sleep(2);
    }

    return 0;
}