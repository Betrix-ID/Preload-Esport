> ![git big](/Esport/img/IFS.png)

<h1>♨️ Preload Esport - Game Performance Booster Utility</h1><hr/>> [!NOTE] Deskripsi:

Script C++ ini dirancang untuk meningkatkan performa game di Android dengan melakukan preload terhadap file library, cache, dan resource penting sebelum game dijalankan.




<hr/>> [!IMPORTANT] Fitur Utama:

1. Preload High Mode: Melakukan preload agresif dengan library dan cache Vulkan/OpenGL sebelum game berjalan.
2. Preload Low Mode: Preload ringan untuk sistem Android agar performa UI tetap responsif.
3. Auto Detection: Mendeteksi game yang sedang berjalan lalu aktifkan preload dinamis.
4. Kill System: Menghentikan preload saat game ditutup atau tidak aktif.
5. NFC Notification: Menampilkan notifikasi sistem via shell tanpa UI.

Efek tergantung pada device, Android version, dan game yang dimainkan.



<hr/>> [!TIP] Tips Penggunaan:

Pastikan Android mendukung akses root agar preload bisa optimal.
Letakkan Gamelist.txt di folder /sdcard/Esport/ yang berisi package name game.
Cek status preload dengan: <code>ps -ef | grep PerloadEsport</code>




<hr/>> [!WARNING] Lisensi & Kredit:

Harap sertakan credit jika menggunakan ulang script ini.
Dilarang memodifikasi dan menyebarkan tanpa mencantumkan sumber.
Penggunaan sembarangan bisa menyebabkan penggunaan RAM berlebih atau crash.




<hr/><h2>🚀 Cara Pakai</h2><pre><code>PerloadEsport [OPTION]
</code></pre><table>
<thead>
<tr><th>Opsi</th><th>Deskripsi</th></tr>
</thead>
<tbody>
<tr><td><code>-L</code></td><td>Aktifkan preload dengan mode cache (lebih agresif).</td></tr>
<tr><td><code>-dL &lt;file&gt;</code></td><td>Preload satu file secara manual (debug mode).</td></tr>
<tr><td><code>-v</code></td><td>Tampilkan info memori dan status preload.</td></tr>
<tr><td><code>-k</code></td><td>Hentikan semua preload yang aktif (kill).</td></tr>
</tbody>
</table><hr/><h2>📚 Contoh Penggunaan</h2><pre><code># Mulai preload sistem dengan mode cache (disarankan sebelum game dibuka)
PerloadEsport -L

# Hanya preload 1 file library secara manual
PerloadEsport -dL /vendor/lib64/libGLES_mali.so

# Cek status preload dan info RAM
PerloadEsport -v

# Hentikan semua preload yang sedang berjalan
PerloadEsport -k
</code></pre><hr/><h2>ℹ️ Info Tambahan</h2><ul>
<li><b>Lokasi File Game</b>: /sdcard/Esport/Gamelist.txt</li>
<li><b>Preload Log</b>: gunakan <code>logcat</code> atau <code>ps</code> untuk melihat proses preload</li>
<li><b>Tips</b>: Reboot setelah penggunaan intens agar sistem tetap segar</li>
</ul><hr/><div align="center" style="font-family: Arial, sans-serif;">  <h2>🙌 Dukung Project Ini</h2>
  <p>Follow, support, atau traktir kopi!</p>  <div style="margin: 20px 0;">
    <a href="https://www.instagram.com/pai_calll?igsh=OGZnYmZ5OGdiMG9r" target="_blank" style="text-decoration: none;">
      <img src="https://img.shields.io/badge/-Instagram-red?style=for-the-badge&logo=instagram&logoColor=white" alt="Instagram">
    </a>
    <a href="https://www.tiktok.com/@pai.call" target="_blank" style="text-decoration: none;">
      <img src="https://img.shields.io/badge/-TikTok-black?style=for-the-badge&logo=tiktok&logoColor=white" alt="TikTok">
    </a>
    <a href="https://saweria.co/Uniccc" target="_blank" style="text-decoration: none;">
      <img src="https://img.shields.io/badge/-Saweria-yellow?style=for-the-badge&logo=saweria&logoColor=white" alt="Saweria">
    </a>
    <a href="https://t.me/Yeye_PID" target="_blank" style="text-decoration: none;">
      <img src="https://img.shields.io/badge/-Telegram-blue?style=for-the-badge&logo=telegram&logoColor=white" alt="Telegram">
    </a>
  </div>  <hr style="border: none; height: 1px; background: #ddd; margin: 40px 0;"></div>
---
