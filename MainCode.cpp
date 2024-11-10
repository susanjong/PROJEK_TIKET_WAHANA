#include <iostream>
#include <queue>
#include <deque>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct PesananTiket {
    string nama;
    int jumlahTiket;
    bool isVIP;
    int nomorPesanan;
};

// Deklarasi antrian untuk pesanan reguler dan linked list untuk pesanan VIP
deque<PesananTiket> antrianHalilintar;
deque<PesananTiket> antrianHysteria;
deque<PesananTiket> antrianArungJeram;
deque<PesananTiket> antrianTornado;
deque<PesananTiket> antrianKoraKora;

queue<PesananTiket> antrianReguler;
list<PesananTiket> antrianVIP;
list<PesananTiket> riwayatPesanan;
int nomorpesanansekarang = 1;

void tambahKeAntrianWahana(string nama, int pilihanWahana) {
    // Cari nama di riwayat pesanan
    bool ditemukanDiRiwayat = false;
    PesananTiket pesanan;
    for (const auto &p : riwayatPesanan) {
        if (p.nama == nama) {
            pesanan = p;
            ditemukanDiRiwayat = true;
            break;
        }
    }

    // Jika nama ditemukan di riwayat, tambahkan ke antrian wahana yang dipilih
    if (ditemukanDiRiwayat) {
        deque<PesananTiket>* antrianWahana;
        if (pilihanWahana == 1) antrianWahana = &antrianHalilintar;
        else if (pilihanWahana == 2) antrianWahana = &antrianHysteria;
        else if (pilihanWahana == 3) antrianWahana = &antrianArungJeram;
        else if (pilihanWahana == 4) antrianWahana = &antrianTornado;
        else if (pilihanWahana == 5) antrianWahana = &antrianKoraKora;
        // Tambahkan wahana lainnya di sini jika diperlukan

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

void JumlahAntrian (int pilihanWahana){
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

// Fungsi untuk menambah pesanan
void tambahPesanan(string nama, int jumlahtiket, bool isVIP) {
     if (!ceknama(nama)) {
        cout << "Nama " << nama << " sudah terdaftar. Silakan gunakan nama lain.\n";
        return;
    }

    PesananTiket pesanan = {nama, jumlahtiket, isVIP, nomorpesanansekarang++};
    if (isVIP) {
        antrianVIP.push_back(pesanan);
        cout << "Pesanan VIP ditambahkan. Nomor pesanan: " << pesanan.nomorPesanan << "\n";
    } else {
        antrianReguler.push(pesanan);
        cout << "Pesanan Reguler ditambahkan. Nomor pesanan: " << pesanan.nomorPesanan << "\n";
    }
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
                 << " - " << pesanan.jumlahTiket << " tiket (VIP)\n";
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
                 << " - " << pesanan.jumlahTiket << " tiket\n";
        }
    }
}

// Fungsi untuk melihat riwayat pesanan
void lihatRiwayatPesanan() {
    cout << "\nRiwayat Pesanan: ";
    if (riwayatPesanan.empty()) {
        cout << "0\n";  // Jika tidak ada riwayat pesanan
    } else {
        for (const auto &pesanan : riwayatPesanan) {
            cout << "\nPesanan #" << pesanan.nomorPesanan << ": " << pesanan.nama
                 << " - " << pesanan.jumlahTiket << " tiket";
        }
    }
    cout<<endl;
}


// Fungsi untuk menghitung dan menampilkan estimasi waktu tunggu
void hitungWaktuTunggu() {
    int waktuPerPesanan = 5; // Asumsi 5 menit per pesanan
    int waktuTunggu = (antrianVIP.size() + antrianReguler.size()) * waktuPerPesanan;
    cout << "\nEstimasi waktu tunggu: " << waktuTunggu << " menit\n";
}

// Fungsi untuk menyelesaikan pesanan berikutnya dan memindahkannya ke riwayat
void selesaikanPesanan() {
    if (!antrianVIP.empty()) {
        riwayatPesanan.push_back(antrianVIP.front());
        cout << "\nPesanan VIP untuk " << antrianVIP.front().nama << " telah selesai.\n";
        antrianVIP.pop_front();
    } else if (!antrianReguler.empty()) {
        riwayatPesanan.push_back(antrianReguler.front());
        cout << "\nPesanan reguler untuk " << antrianReguler.front().nama << " telah selesai.\n";
        antrianReguler.pop();
    } else {
        cout << "\nTidak ada pesanan yang menunggu untuk diselesaikan.\n";
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
    int pilihan, pilihanWahana, opsiWahana;
    string kegiatan, namaTiket;

    system("cls");

    spasiInterface (1);
    Tutup();
    cout << "@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@|  Welcome to Dufan  |@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@#@\n";
    Tutup();
    spasiInterface (1);
    spasiInterface (2);
    cout << "Press Any Button";
    getchar();

    while (true) {
    system("cls");
    cout << "Input Kegiatan [Wahana, Pemesanan Tiket] : ";
    getline(cin, kegiatan);

    for (char &c : kegiatan) {
        c = tolower(c);
    }

    if (kegiatan == "wahana"){
        while (true) {
            system("cls");
            cout << "--- Daftar Wahana ---\n\n";
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

            if (pilihanWahana >= 1 && pilihanWahana <= 5){
                cout << "--- Selamat Datang ---\n";
                cout << "1. Masuk ke Antrian\n";
                cout << "2. Cek Jumlah Antrian\n";
                cout << "\nPilih Opsi: ";
                cin >> opsiWahana;
                cin.ignore();
                system ("cls");

                if (opsiWahana == 1){  
                    cout<< "Masukkan Nama Pengunjung untuk Melakukan Pemeriksaan Tiket: ";
                    cin>> namaTiket;
                    tambahKeAntrianWahana(namaTiket, pilihanWahana);
                    getchar();
                }

                else if (opsiWahana == 2){
                    JumlahAntrian (pilihanWahana);
                }            
            }

            else if (pilihanWahana == 6){
                break;
            }

            cout << "\n[Tekan Enter untuk kembali ke Daftar Wahana]";
            getchar();
    }
    }

    else if (kegiatan == "pemesanan tiket") {
        while (true) {
            system("cls");
            cout << "--- Sistem Pemesanan Tiket ---\n\n";
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
                int jumlahTiket;
                char pilihanVIP;
                bool isVIP = false;

                cout << "Masukkan nama: ";
                cin >> nama;
                cout << "Masukkan jumlah tiket: ";
                cin >> jumlahTiket;
                cout << "Apakah tiket VIP? (y/n): ";
                cin >> pilihanVIP;

                if (pilihanVIP == 'y' || pilihanVIP == 'Y') {
                    isVIP = true;
                }

                tambahPesanan(nama, jumlahTiket, isVIP);
                getchar();

            } else if (pilihan == 2) {
                int nomorPesanan;
                cout << "Masukkan nomor pesanan yang ingin dibatalkan: ";
                cin >> nomorPesanan;
                batalkanPesanan(nomorPesanan);
                getchar();

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
            } else {
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            }

            cout << "\n[Tekan Enter untuk kembali ke Sistem Pemesanan Tiket]";
            getchar();
        }
    } else {
        cout << "Pilihan kegiatan tidak valid. Silakan coba lagi.\n";
        cout << "\n[Tekan Enter untuk kembali ke menu utama]";
        getchar();
    }
}


return 0;
}


