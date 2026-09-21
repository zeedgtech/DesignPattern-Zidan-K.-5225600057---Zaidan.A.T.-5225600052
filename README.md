balatroProject-8
Refleksi Task 1 - Balatro-Like Run Loop

1. **Apa yang jadi bagian tetap (invariant) di program?**
Bagian yang tidak boleh berubah itu alur utama permainan yang ada di dalam class `RunSession`. Urutan 3 ronde sama 6 fase di dalamnya (mulai dari bikin input, hitung skor, hitung reward, update duit, mampir shop, sampe lanjut ronde) sudah dipatok mati dan tidak boleh diubah-ubah posisinya.

2. **Bagian mana saja yang bisa diubah-ubah (mutable)?**
Bagian yang fleksibel tuh logic-nya yang dibikin pake interface, kayak cara dapet input (`IInputGenerator`), cara hitung skor (`IScoringRule`), sama cara hitung reward (`IRewardRule`). Jadi kita bisa ganti-ganti isinya kapan aja tanpa ngerusak struktur utama game-nya.

3. **Kenapa waktu `InputGenerator`-nya diganti, tetapi `RunSession` tidak ikut ter ubah?**
Karena `RunSession` dari awal cuma kenal sama interface-nya doang, bukan class aslinya. Jadi waktu kemarin kita ganti jadi `RandomInputGenerator`, tinggal dipasang aja dari luar pake *dependency injection*. Si `RunSession` anteng aja karena dia cuma nerima hasil jadinya tanpa peduli cara dapet inputnya gimana.

4. **Seandainya logic scoring disimpan langsung di dalam `RunSession`, apa yang akan terjadi?**
Bakal kacau sih. Kalau dicampur aduk di situ, nanti tiap kali ada perubahan rules atau mau nambah fitur, kita jadi terpaksa bongkar-bongkar class `RunSession` lagi. Risikonya urutan fesenya malah jadi berantakan (rusak invariant-nya) dan kodenya jadi susah diurus ke depannya.