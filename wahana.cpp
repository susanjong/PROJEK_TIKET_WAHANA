#include <iostream>
#include <queue>
#include <deque>
#include <list>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <iomanip>


using namespace std;

struct PesananTiket {
    string nama;
    bool isVIP;  // Karena hanya bisa beli satu tiket, kita hanya perlu status VIP
    int nomorPesanan;
};

struct LogAktivitas {
    string nama;
    string aksi;
    std::chrono::time_point<std::chrono::system_clock> waktu;
};

vector<LogAktivitas> logAktivitas;

// Deklarasi antrian untuk pesanan wahana dan tiket
deque<PesananTiket> antrianHalilintar;
deque<PesananTiket> antrianHysteria;
deque<PesananTiket> antrianArungJeram;
deque<PesananTiket> antrianTornado;
deque<PesananTiket> antrianKoraKora;

queue<PesananTiket> antrianReguler;
list<PesananTiket> antrianVIP;
list<PesananTiket> riwayatPesanan;
int nomorpesanansekarang = 1;

// Fungsi untuk mencatat aktivitas
void catatAktivitas(const string& nama, const string& aksi) {
    logAktivitas.push_back({nama, aksi, std::chrono::system_clock::now()});
}

// Fungsi untuk menampilkan log aktivitas
void lihatLogAktivitas() {
    cout << "\n--- Log Aktivitas ---\n";
    if (logAktivitas.empty()) {
        cout << "Belum ada aktivitas yang tercatat.\n";
        return;
    }
    for (const auto& log : logAktivitas) {
        time_t waktu = std::chrono::system_clock::to_time_t(log.waktu);
        cout << "[" << put_time(localtime(&waktu), "%Y-%m-%d %H:%M:%S") << "] "
            << log.nama << " - " << log.aksi << endl;
    }
}

// Fungsi cek status tiket di wahana
void cekStatusDiWahana(string nama) {
    deque<PesananTiket>* wahanas[] = {&antrianHalilintar, &antrianHysteria, &antrianArungJeram, &antrianTornado, &antrianKoraKora};
    string namaWahana[] = {"Halilintar", "Hysteria", "Arung Jeram", "Tornado", "Kora-Kora"};

    bool ditemukan = false;
    for (int i = 0; i < 5; ++i) {
        int posisi = 1;
        for (const auto& p : *wahanas[i]) {
            if (p.nama == nama) {
                cout << nama << " ada di wahana " << namaWahana[i] << ", posisi antrian: " << posisi << endl;
                ditemukan = true;
            }
            ++posisi;
        }
    }
    if (!ditemukan) {
        cout << nama << " tidak ditemukan di antrian wahana manapun.\n";
    }
}

// Estimasi waktu tunggu per wahana
void estimasiWaktuPerWahana(int pilihanWahana) {
    deque<PesananTiket>* antrianWahana;
    if (pilihanWahana == 1) antrianWahana = &antrianHalilintar;
    else if (pilihanWahana == 2) antrianWahana = &antrianHysteria;
    else if (pilihanWahana == 3) antrianWahana = &antrianArungJeram;
    else if (pilihanWahana == 4) antrianWahana = &antrianTornado;
    else if (pilihanWahana == 5) antrianWahana = &antrianKoraKora;
    else {
        cout << "Pilihan wahana tidak valid.\n";
        return;
    }

    int waktuPerPengunjung = 5; // Asumsi waktu rata-rata bermain 5 menit
    int estimasi = antrianWahana->size() * waktuPerPengunjung;
    cout << "Estimasi waktu tunggu di wahana ini: " << estimasi << " menit.\n";
}

// Fungsi untuk melihat daftar aktivitas tambahan di menu utama
void lihatDaftarFitur() {
    cout << "\n--- Fitur Tambahan ---\n";
    cout << "1. Cek Status di Wahana\n";
    cout << "2. Estimasi Waktu Tunggu Per Wahana\n";
    cout << "3. Lihat Log Aktivitas\n";
    cout << "4. Kembali ke Menu Utama\n";
    cout << "Pilih opsi: ";
}

// Tambahan di main menu
void menuFiturTambahan() {
    while (true) {
        
        lihatDaftarFitur();
        int pilihan;
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string nama;
            cout << "Masukkan nama pengguna: ";
            cin >> nama;
            cekStatusDiWahana(nama);
        } else if (pilihan == 2) {
            int pilihanWahana;
            cout << "\n--- Pilih Wahana ---\n";
            cout << "1. Halilintar\n";
            cout << "2. Hysteria\n";
            cout << "3. Arung Jeram\n";
            cout << "4. Tornado\n";
            cout << "5. Kora-Kora\n";
            cout << "Pilihan: ";
            cin >> pilihanWahana;
            estimasiWaktuPerWahana(pilihanWahana);
        } else if (pilihan == 3) {
            lihatLogAktivitas();
        } else if (pilihan == 4) {
            break;
        }

        cout << "\n[Tekan Enter untuk kembali ke menu fitur tambahan]";
        getchar();
    }
}

// Fungsi untuk menambah pesanan tiket
bool ceknama(const string &nama) {
    // Cek di antrian VIP
    for (const auto &pesanan : antrianVIP) {
        if (pesanan.nama == nama) return false;
    }

    // Cek di antrian reguler
    queue<PesananTiket> tempAntrian = antrianReguler;
    while (!tempAntrian.empty()) {
        if (tempAntrian.front().nama == nama) return false;
        tempAntrian.pop();
    }
    return true;
}

void tambahPesanan(string nama, bool isVIP) {
    if (!ceknama(nama)) {
        cout << "Nama " << nama << " sudah terdaftar. Silakan gunakan nama lain.\n";
        return;
    }

    PesananTiket pesanan = {nama, isVIP, nomorpesanansekarang++};
    if (isVIP) {
        antrianVIP.push_back(pesanan);
        cout << "Pesanan VIP ditambahkan. Nomor pesanan: " << pesanan.nomorPesanan << "\n";
    } else {
        antrianReguler.push(pesanan);
        cout << "Pesanan Reguler ditambahkan. Nomor pesanan: " << pesanan.nomorPesanan << "\n";
    }
}

// Fungsi untuk menambahkan ke antrian wahana
void tambahKeAntrianWahana(string nama, int pilihanWahana) {
    bool ditemukanDiRiwayat = false;
    PesananTiket pesanan;
    for (const auto &p : riwayatPesanan) {
        if (p.nama == nama) {
            pesanan = p;
            ditemukanDiRiwayat = true;
            break;
        }
    }

    if (ditemukanDiRiwayat) {
        deque<PesananTiket>* antrianWahana;
        if (pilihanWahana == 1) antrianWahana = &antrianHalilintar;
        else if (pilihanWahana == 2) antrianWahana = &antrianHysteria;
        else if (pilihanWahana == 3) antrianWahana = &antrianArungJeram;
        else if (pilihanWahana == 4) antrianWahana = &antrianTornado;
        else if (pilihanWahana == 5) antrianWahana = &antrianKoraKora;

        // Pengecekan apakah jumlah orang di antrian wahana sudah mencapai 5
        if (antrianWahana->size() >= 5) {
            cout << "Wahana sudah penuh, maksimal 5 orang per wahana.\n";
            return;
        }

        // Penambahan pengguna ke antrian berdasarkan status VIP atau reguler
        if (pesanan.isVIP) {
            // Jika VIP, tambahkan setelah semua VIP yang ada
            auto pos = antrianWahana->begin();
            while (pos != antrianWahana->end() && pos->isVIP) {
                ++pos;
            }
            antrianWahana->insert(pos, pesanan);
            cout << "Pengguna VIP " << nama << " telah ditambahkan ke antrian wahana.\n";
        } else {
            // Jika reguler, tambahkan di belakang semua pengguna (VIP dan reguler)
            antrianWahana->push_back(pesanan);
            cout << "Pengguna Reguler " << nama << " telah ditambahkan ke antrian wahana.\n";
        }

        // Hitung posisi dalam antrian
        int posisi = 1;
        for (const auto &p : *antrianWahana) {
            if (p.nama == nama) break;
            posisi++;
        }
        cout << "\nPosisi dalam antrian: " << posisi << "\n";
    } else {
        system("cls");
        cout << "Pengguna " << nama << " tidak memiliki tiket valid untuk naik wahana.\n";
        cout << "Silahkan Selesaikan Pesanan atau Melakukan Pembelian Tiket\n";
    }
}

// Fungsi untuk melihat jumlah antrian di wahana
void JumlahAntrian(int pilihanWahana) {
    deque<PesananTiket>* antrianWahana;

    if (pilihanWahana == 1) antrianWahana = &antrianHalilintar;
    else if (pilihanWahana == 2) antrianWahana = &antrianHysteria;
    else if (pilihanWahana == 3) antrianWahana = &antrianArungJeram;
    else if (pilihanWahana == 4) antrianWahana = &antrianTornado;
    else if (pilihanWahana == 5) antrianWahana = &antrianKoraKora;
    else {
        cout << "Pilihan wahana tidak valid.\n";
        return;
    }

    cout << "Jumlah antrian untuk wahana sekarang: " << antrianWahana->size() << endl;
}

void kosongkanAntrianWahana(int pilihanWahana) {
    deque<PesananTiket>* antrianWahana;

    if (pilihanWahana == 1) antrianWahana = &antrianHalilintar;
    else if (pilihanWahana == 2) antrianWahana = &antrianHysteria;
    else if (pilihanWahana == 3) antrianWahana = &antrianArungJeram;
    else if (pilihanWahana == 4) antrianWahana = &antrianTornado;
    else if (pilihanWahana == 5) antrianWahana = &antrianKoraKora;
    else {
        cout << "Pilihan wahana tidak valid.\n";
        return;
    }

    // Mengosongkan seluruh antrian wahana
    antrianWahana->clear();
    cout << "Semua orang telah selesai bermain di wahana ini. Antrian telah dikosongkan.\n";
}

// Fungsi untuk membatalkan pesanan berdasarkan nomor pesanan
void batalkanPesanan(int nomorPesanan) {
    bool ditemukan = false;

    // Cek antrian reguler
    queue<PesananTiket> antrianSementara;
    while (!antrianReguler.empty()) {
        PesananTiket pesanan = antrianReguler.front();
        antrianReguler.pop();
        if (pesanan.nomorPesanan == nomorPesanan) {
            cout << "Pesanan #" << nomorPesanan << " berhasil dibatalkan.\n";
            ditemukan = true;
        } else {
            antrianSementara.push(pesanan);
        }
    }
    antrianReguler = antrianSementara;

    // Cek antrian VIP
    auto it = remove_if(antrianVIP.begin(), antrianVIP.end(), [nomorPesanan](const PesananTiket &pesanan) {
        return pesanan.nomorPesanan == nomorPesanan;
    });

    if (it != antrianVIP.end()) {
        antrianVIP.erase(it, antrianVIP.end());
        cout << "Pesanan VIP #" << nomorPesanan << " berhasil dibatalkan.\n";
        ditemukan = true;
    }

    if (!ditemukan) {
        cout << "Pesanan #" << nomorPesanan << " tidak ditemukan.\n";
    }
}

// Fungsi untuk melihat pesanan yang belum diproses
void lihatPesananPending() {
    cout << "\nPesanan VIP yang Belum Diproses: ";
    if (antrianVIP.empty()) {
        cout << "0";  // Jika tidak ada pesanan VIP yang pending
    } else {
        cout << endl;
        for (const auto &pesanan : antrianVIP) {
            cout << "Pesanan #" << pesanan.nomorPesanan << ": " << pesanan.nama
                 << " (VIP)\n";
        }
    }

    cout << "\nPesanan Reguler yang Belum Diproses: ";
    if (antrianReguler.empty()) {
        cout << "0\n";  // Jika tidak ada pesanan reguler yang pending
    } else {
        cout << endl;
        queue<PesananTiket> antrianSementara = antrianReguler;
        while (!antrianSementara.empty()) {
            PesananTiket pesanan = antrianSementara.front();
            antrianSementara.pop();
            cout << "Pesanan #" << pesanan.nomorPesanan << ": " << pesanan.nama
                 << " (Reguler)\n";
        }
    }
}

// Fungsi untuk melihat riwayat pesanan
void lihatRiwayatPesanan() {
    cout << "\nRiwayat Pesanan: ";
    if (riwayatPesanan.empty()) {
        cout << "0\n";  // Jika tidak ada riwayat pesanan
    } else {
        // Tampilkan pesanan VIP terlebih dahulu
        for (const auto &pesanan : riwayatPesanan) {
            cout << "\nPesanan #" << pesanan.nomorPesanan << ": " << pesanan.nama;
            if (pesanan.isVIP) {
                cout << " (VIP)\n";
            } else {
                cout << " (Reguler)\n";
            }
        }
    }
    cout << endl;
}


// Fungsi untuk menghitung estimasi waktu tunggu
void hitungWaktuTunggu() {
    int waktuPerPesanan = 5; // Asumsi 5 menit per pesanan
    int waktuTunggu = (antrianVIP.size() + antrianReguler.size()) * waktuPerPesanan;
    cout << "Estimasi waktu tunggu: " << waktuTunggu << " menit.\n";
}

// Fungsi untuk menyelesaikan pesanan
void selesaikanPesanan() {
    // Cek apakah ada pesanan VIP yang belum diproses
    if (!antrianVIP.empty()) {
        riwayatPesanan.push_back(antrianVIP.front());  // Proses pesanan VIP pertama
        antrianVIP.pop_front();  // Hapus pesanan VIP dari antrian
        cout << "Pesanan VIP berikutnya telah diproses.\n";
    } 
    // Jika tidak ada pesanan VIP, cek pesanan reguler
    else if (!antrianReguler.empty()) {
        riwayatPesanan.push_back(antrianReguler.front());  // Proses pesanan reguler pertama
        antrianReguler.pop();  // Hapus pesanan reguler dari antrian
        cout << "Pesanan Reguler berikutnya telah diproses.\n";
    } 
    // Jika tidak ada pesanan sama sekali
    else {
        cout << "Tidak ada pesanan yang perlu diproses.\n";
    }
}

void spasiInterface (int n){
    if (n==1){
        for (int i = 1; i <= 5 ; i++) 
        cout << "\n";
    }
    else if (n == 2){
        for (int i = 1; i <= 48; i++)
        cout << " ";
    }   
}

void Tutup () {
    cout << "@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@| ------------------ |@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@\n";
}


int main() {
    int pilihan, pilihanWahana, opsiWahana, pil;
    string kegiatan, namaTiket;
    
    spasiInterface (1);
    Tutup();
    cout << "@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@|  Welcome to Dufan  |@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@\n";
    Tutup();

     // Teks yang akan dipusatkan
    string text = "Taman Impian Jaya Ancol, Jalan Lodan Timur Nomor 7, Ancol, Kecamatan Pademangan, Jakarta Utara.";

    // Menentukan lebar terminal untuk teks
    int terminal_width_text = 115;  // Lebar terminal untuk teks
    int padding_text = (terminal_width_text - text.length()) / 2;

    cout << endl;
    cout << setw(padding_text + text.length()) << setiosflags(ios::right) << text << endl;
cout << endl;
cout << endl;

    // Mendapatkan waktu saat ini
    time_t ct = time(0);
    string currenttime = ctime(&ct);

    // Menghapus karakter newline ('\n') di akhir string waktu
    currenttime.erase(currenttime.length() - 1);

    // Menentukan lebar terminal untuk waktu
    int terminal_width_time = 110;  
    int padding_time = (terminal_width_time - currenttime.length()) / 2;

    cout << setw(padding_time + currenttime.length()) << setiosflags(ios::right) << currenttime << endl;
    spasiInterface (1);
    spasiInterface (2);

    cout << "Press Any Button";
    getchar();

    while (true) {
        system("cls");
        cout << "1. Wahana\n";
        cout << "2. Pemesanan Tiket\n";
        cout << "3. Menu Tambahan\n";
        cout << "4. Keluar\n";
        cout << "Masukkan kegiatan yang ingin Anda lakukan : ";
        getline(cin, kegiatan);
        transform(kegiatan.begin(), kegiatan.end(), kegiatan.begin(), ::tolower);

        if (kegiatan == "1") {
            while (true) {
               
                cout << "\n--- Daftar Wahana ---\n";
                cout << "1. Halilintar\n";
                cout << "2. Hysteria\n";
                cout << "3. Arung Jeram\n";
                cout << "4. Tornado\n";
                cout << "5. Kora-Kora\n";
                cout << "6. Keluar\n\n";
                cout << "Pilih Opsi: ";
                cin >> pilihanWahana;
                cin.ignore();
                system("cls");

                if (pilihanWahana >= 1 && pilihanWahana <= 5) {
                    cout << "--- Selamat Datang ---\n";
                    cout << "1. Masuk ke Antrian\n";
                    cout << "2. Cek Jumlah Antrian\n";
                    cout << "3. Selesaikan Wahana\n";
                    cout << "\nPilih Opsi: ";
                    cin >> opsiWahana;
                    cin.ignore();
                    system("cls");

                    if (opsiWahana == 1) {
                        cout << "Masukkan Nama Pengunjung untuk Melakukan Pemeriksaan Tiket: ";
                        cin >> namaTiket;
                        tambahKeAntrianWahana(namaTiket, pilihanWahana);
                    } else if (opsiWahana == 2) {
                        JumlahAntrian(pilihanWahana);
                    } else if (opsiWahana == 3) {
                        kosongkanAntrianWahana(pilihanWahana);
                    }
                } else if (pilihanWahana == 6) {
                    break;
                }
                cout << "\n[Tekan Enter untuk kembali ke Daftar Wahana]";
                getchar();
            }
        }
        else if (kegiatan == "2") {
            while (true) {
                
                cout << "\n--- Sistem Pemesanan Tiket ---\n";
                cout << "1. Tambah Pesanan\n";
                cout << "2. Batalkan Pesanan\n";
                cout << "3. Lihat Pesanan yang Belum Diproses\n";
                cout << "4. Cek Estimasi Waktu Tunggu\n";
                cout << "5. Lihat Riwayat Pesanan\n";
                cout << "6. Selesaikan Pesanan Berikutnya\n";
                cout << "7. Keluar\n\n";
                cout << "Pilih opsi: ";
                cin >> pilihan;
                cin.ignore();
                system("cls");

                if (pilihan == 1) {
                    string nama;
                    char pilihanVIP;
                    bool isVIP = false;

                    cout << "Masukkan nama: ";
                    cin >> nama;
                    cout << "Apakah tiket VIP? (y/n): ";
                    cin >> pilihanVIP;

                    if (pilihanVIP == 'y' || pilihanVIP == 'Y') {
                        isVIP = true;
                    }
                    tambahPesanan(nama, isVIP);
                } else if (pilihan == 2) {
                    int nomorPesanan;
                    cout << "Masukkan nomor pesanan yang ingin dibatalkan: ";
                    cin >> nomorPesanan;
                    batalkanPesanan(nomorPesanan);
                } else if (pilihan == 3) {
                    lihatPesananPending();
                } else if (pilihan == 4) {
                    hitungWaktuTunggu();
                } else if (pilihan == 5) {
                    lihatRiwayatPesanan();
                } else if (pilihan == 6) {
                    selesaikanPesanan();
                } else if (pilihan == 7) {
                    break;
                }
                cout << "\n[Tekan Enter untuk kembali ke Sistem Pemesanan Tiket]";
                getchar();
            }
        }

        else if (kegiatan == "3") {
            menuFiturTambahan();
        }

        else {
        cout << "Terima kasih sudah bermain di DUFAN! Sampai jumpa lagi!!" << endl;
        break;
        }
    }

    return 0;
}
