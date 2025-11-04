# snake-games

Program ini dibuat untuk melatih penguasaan saya dalam C++.

## Deskripsi

Project ini adalah game Snake sederhana yang berjalan di konsol Windows. Permainan menampilkan papan 40x20 dengan batas, makanan acak, skor, dan peningkatan kecepatan setiap kali ular memakan makanan. Game berakhir jika ular menabrak dinding atau menabrak tubuhnya sendiri.

## Persyaratan

- Windows
- Compiler C++ (contoh: MinGW `g++` atau MSVC)

## Cara Build (dengan g++)

Jalankan perintah berikut di PowerShell pada folder project:

```
g++ snake.cpp -o snake.exe
```

Alternatif (MSVC Developer Command Prompt):

```
cl /EHsc snake.cpp
```

## Cara Menjalankan (PowerShell)

```
.\snake.exe
```

## Kontrol

- Panah Atas/Bawah/Kiri/Kanan atau WASD untuk bergerak
- ESC untuk keluar

## Catatan Teknis

- Input non-blocking menggunakan `conio.h` (`_kbhit`, `_getch`).
- Timing menggunakan `Sleep` dari `windows.h`.
- Rendering dilakukan dengan memindahkan posisi kursor (tanpa clear screen penuh) agar layar tidak berkedip.

## Struktur Utama Kode

- Ukuran papan: 40 (lebar) x 20 (tinggi)
- Ular disimpan sebagai `deque<Point>` (kepala di depan)
- Makanan ditempatkan pada sel acak yang kosong
- Skor bertambah 10 setiap makanan dimakan; kecepatan meningkat bertahap

## Troubleshooting Cepat

- Pastikan compiler terpasang: `g++ --version` atau gunakan MSVC `cl` dari "Developer Command Prompt for VS".
- Jika perintah run gagal, gunakan format PowerShell: `.\snake.exe` (bukan `./snake.exe`).
- Jika error include: pastikan Anda compile di Windows (file memakai `windows.h` dan `conio.h`).

Selamat bermain! 🎮🐍
