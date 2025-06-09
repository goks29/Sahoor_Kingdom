Cara Menjalankan :

- git clone https://github.com/goks29/Sahoor_Kingdom
- buka git bash
- ./run.sh
- Jika tidak menggunakan git bash
- gcc -o out/main.exe library/*.c -Iinclude
- out\main.exe




Program ini dirancang untuk membantu Anda mengelola dan menjelajahi silsilah keluarga secara interaktif. Ikuti langkah-langkah berikut untuk memulai:

1.	Menjalankan Program
    •	Jalankan file main.c untuk memulai aplikasi.
    •	Program akan otomatis menginisialisasi pohon keluarga kosong dengan memanggil InitNbTree(&tree).

2.	Memuat Data Awal (Jika Ada)
    •	Program akan mencoba memuat data keluarga dari file menggunakan getDataFromFile(&tree).
    •	Jika file tersedia, struktur pohon akan langsung terisi dengan data yang tersimpan sebelumnya.
    •	Informasi keluarga akan ditampilkan di konsol melalui printFromFile("SahoorFamily.txt").

3.	Mengecek Status Pohon
    •	Program akan memeriksa apakah pohon keluarga masih kosong menggunakan IsEmptyTree(&tree).
    •	Jika kosong, Anda akan diminta menambahkan leluhur pertama sebagai akar pohon.

4.	Menambahkan Leluhur (Jika Belum Ada)
Gunakan opsi InsertLeluhur(&tree) untuk mengisi leluhur pertama:
    •	Masukkan nama, usia, dan jenis kelamin leluhur sesuai permintaan.
    •	Data akan disimpan dan dijadikan akar dalam struktur pohon.

5.	Menu Utama
Setelah pohon terisi, Anda akan masuk ke Menu Utama. Pilih opsi dengan memasukkan nomor sesuai:
  	1. Tambah Pasangan
    Tambahkan pasangan untuk anggota keluarga tertentu.
    
    2. Tambah Anak
    Tambahkan anak untuk orang tua tertentu.
    
    3. Cek Hubungan Keluarga
    Periksa hubungan antara dua anggota keluarga.
    
    4. Waris Harta
    Hitung pembagian harta warisan dari anggota yang telah meninggal.
    
    5. Tambah Keluarga Pasangan
    Tambahkan data orang tua dan saudara dari pasangan yang sudah ada.
    
    6. Time Skip
    Tambahkan usia semua anggota keluarga sejumlah tahun tertentu.
    
    7. Print Tree
    Tampilkan seluruh silsilah keluarga dalam bentuk pohon.
    
    0. Keluar
    Keluar dari program dan simpan data secara otomatis.


6.	Menyimpan dan Keluar
    •	Saat memilih opsi [0], program akan menyimpan seluruh data ke file jika ada perubahan.
    •	Anda dapat melanjutkan sesi selanjutnya dengan data yang sama.
    •	Pastikan data yang dimasukkan valid (misalnya usia masuk akal, jenis kelamin sesuai).
    •	Gunakan fitur dengan bijak untuk menjaga konsistensi struktur pohon keluarga.
    •	Jika terjadi kesalahan input, pesan kesalahan akan muncul di konsol secara otomatis.
