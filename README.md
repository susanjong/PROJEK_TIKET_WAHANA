# PROJEK_TIKET_WAHANA
Tugas ini dibuat untuk memenuhi penilaiaan matakuliah Struktur Data semester 3, Universitas Sumatera Utara 
Anggota Kelompok: 
1. Susan Jong (231401014)
2. Clarissa Halim (231401020)
3. Muhammad Rifki Bariq (231401089)
4. Ferarine (231401095)
5. Fathurrahman Nasution (23140110)
Kelas: KOM B (2023)

Jurusan : Ilmu Komputer
Fakultas: Ilmu Komputer dan Teknologi Informasi 

Dosen Pengampu : Anandhini Medianty Nababan, S.Kom, M.T

## Deskripsi Program  
Ini adalah projek codingan yang kami buat dengan tema projek tiket wahana untuk lokasi di Dufan, Jakarta Utara. 
Program ini adalah simulasi sistem manajemen tiket dan antrian di sebuah taman hiburan, dengan beberapa wahana yang dapat dipilih oleh pengunjung. Program ini mencatat aktivitas, menangani pesanan tiket (baik VIP maupun reguler), serta mengelola antrian wahana. Beberapa fitur yang terdapat dalam program ini adalah pencatatan log aktivitas, estimasi waktu tunggu, pengecekan status antrian, serta pengelolaan pesanan tiket dan antrian wahana.

## Struktur Data
1. PesananTiket: Struktur ini menyimpan data mengenai nama pengunjung, apakah tiket tersebut VIP atau reguler, serta nomor pesanan.
2. LogAktivitas: Struktur ini mencatat log aktivitas pengguna dalam sistem, termasuk nama, aksi, dan waktu aktivitas.
3. Antrian: Menggunakan berbagai struktur data untuk menyimpan antrian pengunjung yang ingin naik wahana, termasuk antrian reguler dan VIP.
4. RiwayatPesanan: Menyimpan riwayat pesanan yang telah selesai diproses.

## Fungsi Utama
1. CatatAktivitas: Fungsi ini digunakan untuk mencatat aktivitas pengguna dalam sistem, seperti membeli tiket, menambahkan pesanan, atau cek status wahana.
2. LihatLogAktivitas: Fungsi ini menampilkan log aktivitas yang telah tercatat sebelumnya.
3. CekStatusDiWahana: Fungsi untuk mengecek status antrian seorang pengunjung di salah satu wahana. Jika pengunjung ada di antrian, program akan menunjukkan posisi mereka dalam antrian.
4. EstimasiWaktuPerWahana: Fungsi ini menghitung estimasi waktu tunggu berdasarkan jumlah pengunjung yang ada di antrian wahana.
tambahPesanan: Fungsi untuk menambah pesanan tiket, baik tiket reguler maupun VIP, serta memastikan bahwa tidak ada duplikasi nama dalam antrian.
5. TambahKeAntrianWahana: Fungsi untuk menambah pengunjung ke antrian wahana setelah membeli tiket, baik itu VIP atau reguler.
6. BatalkanPesanan: Fungsi ini memungkinkan untuk membatalkan pesanan berdasarkan nomor pesanan yang diberikan.
7. LihatPesananPending: Fungsi ini menampilkan pesanan-pesanan yang belum diproses, baik untuk VIP maupun reguler.
8. HitungWaktuTunggu: Fungsi ini menghitung estimasi total waktu tunggu berdasarkan jumlah pesanan yang ada di antrian VIP dan reguler.
9. SelesaikanPesanan: Fungsi ini digunakan untuk menyelesaikan pesanan, dengan memindahkan pesanan dari antrian VIP atau reguler ke riwayat pesanan setelah diproses.

## Fungsi Tambahan
1. MenuFiturTambahan: Menyediakan menu untuk fitur tambahan seperti melihat status di wahana, estimasi waktu tunggu, dan melihat log aktivitas.
2. JumlahAntrian: Fungsi untuk melihat jumlah orang yang ada di antrian untuk setiap wahana.
3. KosongkanAntrianWahana: Fungsi untuk mengosongkan seluruh antrian wahana setelah semua orang selesai bermain.

## Alur Kerja
1. Pengguna dapat memilih fitur di menu utama, seperti membeli tiket (reguler atau VIP), mengecek status wahana, melihat estimasi waktu tunggu, atau melihat riwayat aktivitas.
2. Pengguna yang ingin naik wahana dapat ditambahkan ke antrian wahana setelah mereka membeli tiket.
3. Pengguna juga dapat membatalkan pesanan atau melihat jumlah antrian untuk setiap wahana.
