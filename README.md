# tugas3-el4121

Repository yang berisikan source code untuk tugas 3 mata kuliah EL4121 Perancangan Sistem Embedded. Pada tugas ini, mahasiswa diminta untuk membuat lampu geser yang bekerja secara sinkron. Tugas ini dibuat dengan esp32 yang diprogram menggunakan ESP-IDF.

## Struktur Folder

```
tugas3-el4121/
|
├─ fsm/ (source code fsm-fsm yang digunakan)
├─ esp/ (source code lampu geser untuk esp32)
|
├─ .gitignore
├─ README.md
├─ Makefile
```

## Panduan Penggunaan

1. Hubungkan pushbutton ke GPIO22 (tombol geser kiri) dan GPIO23 (tombol geser kanan) dengan konfigurasi pulldown
2. Hubungkan empat buah LED ke GPIO16 (paling kiri) hingga GPIO19 (paling kanan) 
3. Program esp32 menggunakan ESP-IDF dengan perintah `idf.py build && idf.py -p (PORT) flash`
