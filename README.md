# Refleksi Task 2 - Core Loop Design

1. **Apa core loop (alur utama) dari game ini?**
Alur permainannya dimulai dari player melakukan input/aksi, sistem mengevaluasi tabrakan atau aksi tersebut, reward atau penalti diberikan, state game (posisi, skor, HP) diupdate, lalu dicek kondisi menang/kalahnya sebelum diulang dari awal.

2. **Apa yang jadi bagian tetap (invariant)?**
Bagian yang tidak boleh berubah adalah urutan fase di dalam `GameSession` (input, sistem evaluasi, update state, dan cek kondisi). Urutan ini harus jalan terus secara berurutan dan tidak boleh dibolak-balik posisinya.

3. **Bagian mana saja yang bisa diubah-ubah (mutable)?**
Bagian data atau parameter pendukung game, seperti multiplier lompatan player, tingkat kemunculan musuh (spawn rate), dan formula perhitungan skor. Bagian ini bebas diubah-ubah untuk balancing game tanpa ngerusak struktur core loop-nya.

4. **Kalau mau nambah fitur baru, class mana yang bakal diubah?**
Yang diubah cukup class spesifik yang bersangkutan saja (misalnya class Player atau System), sedangkan class pengatur utama (`GameSession`) tidak perlu disentuh sama sekali.

5. **Seandainya urutan loop-nya diubah, apa yang bakal terjadi?**
Bakal kacau dan error. Contohnya kalau pengecekan menang/kalah ditaruh sebelum sistem mengevaluasi aksi player, game bakal membaca data lama (basi) yang bikin sistem kematian player atau skor jadi ngaco dan tidak sinkron.