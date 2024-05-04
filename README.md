# Schedulo - Scheduling Program
Schedulo adalah sebuah program berbasis CLI yang dapat digunakan untuk menyusun jadwal dengan mempertimbangkan ketergantungan subject pada setiap kelas. Salah satu penggunaan Schedulo adalah untuk menyusun jadwal ujian setiap mata kuliah dengan pilihan mata kuliah yang berbeda-beda setiap mahasiswa. Schedulo akan membuat graph berdasarkan data mahasiswa dan melakukan pewarnaan graph menggunakan algoritma Welch-Powell. Hasil pewarnaan inilah yang akan menjadi hasil jadwal yang dibuat oleh Schedulo. 

Hasil jadwal berupa daftar beberapa sesi dengan mata kuliah di setiap sesi. Satu sesi merepresentasikan mata kuliah yang dapat dilakukan secara bersamaan. Satu sesi dengan sesi lainnya harus dilakukan pada jadwal yang berbeda.

## Cara Menggunakan
### CLI
1.  Jalankan file schedulo.exe 
2.  Pada menu utama, pilih metode input data
    - Menggunakan File External: untuk menginputkan data menggunakan file .txt pada folder input
    - Input Data Secara Manual: Untuk menginput data secara manual satu persatu
3.  Melakukan input data
4.  Program akan menyusun dan mencetak hasil jadwal
5.  Pilih Simpan ke File External untuk menyimpan hasil jadwal ke file txt atau keluar tanpa menyimpan jadwwal

### Command dengan Argument
1. Buka Terminal (CMD, Powershell, bash, dll) pada folder project.
2. Jalankan perintah untuk memanggil program Schedulo.
```./schedulo -i input.txt -o output.txt --skip```
  - **./schedulo**: untuk memanggil program schedulo.
  - **-i**: argumen untuk memberikan input file, diikuti nama file input txt yang berada didalam folder input.
  - **-o**: argumen untuk menyimpan hasil jadwal ke file external berupa file txt, diikuti nama file yang akan disimpan.
  - **--skip**: untuk melewati semua input konfirmasi

## Nama Kelompok
- 23051204356 Dedy Irama 2023K
- 23051204360 Kenang Banyu Ramadhan_2023K
- 23051204374 Rafi Arnandha Pramudianto_2023K
- 23051204378 Lukman Adi Wijaya_2023K
