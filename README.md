# 🍝 Philosophers

42 School'un klasik Dining Philosophers problemi implementasyonu. Bu proje, multithreading, mutex senkronizasyonu ve deadlock önleme kavramlarını öğretmeyi amaçlar.

## 📖 Problem Tanımı

Yuvarlak bir masada N adet filozof oturmaktadır. Her filozofun önünde bir tabak spagetti ve her iki filozofun arasında bir çatal bulunur. Filozoflar üç aktivite gerçekleştirir:

- 🍴 **Yemek yeme** — İki çatala ihtiyaç duyar (sol ve sağ)
- 💭 **Düşünme** — Çatal gerektirmez
- 😴 **Uyuma** — Yemekten sonra uyur

Bir filozof belirli bir süre yemek yemezse açlıktan ölür. Amaç: Hiçbir filozofun ölmemesini sağlamak.

## 🚀 Kullanım

### Derleme

```bash
make        # Projeyi derle
make clean  # Object dosyalarını temizle
make fclean # Tüm derleme çıktılarını temizle
make re     # Temizle ve yeniden derle
```

### Çalıştırma

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parametreler

| Parametre | Açıklama |
|-----------|----------|
| `number_of_philosophers` | Filozof sayısı (aynı zamanda çatal sayısı) |
| `time_to_die` | Bir filozofun son yemeğinden itibaren ölmeden önce geçebilecek maksimum süre (ms) |
| `time_to_eat` | Bir filozofun yemek yeme süresi (ms) |
| `time_to_sleep` | Bir filozofun uyuma süresi (ms) |
| `number_of_times_each_philosopher_must_eat` | (Opsiyonel) Her filozofun yemesi gereken minimum yemek sayısı |

### Örnek Kullanım

```bash
# 5 filozof, 800ms ölüm süresi, 200ms yemek, 200ms uyku
./philo 5 800 200 200

# Her filozof en az 7 kez yemeli
./philo 5 800 200 200 7

# Ölüm testi (bir filozof ölmeli)
./philo 4 310 200 100
```

## 🔧 Teknik Detaylar

### Kullanılan Teknolojiler

- **Dil:** C
- **Threading:** POSIX Threads (pthread)
- **Senkronizasyon:** Mutex

### İzin Verilen Fonksiyonlar

```c
memset, printf, malloc, free, write,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock

```

```

## 🧠 Algoritma ve Çözüm Yaklaşımı

### Deadlock Önleme

Deadlock'u önlemek için çeşitli stratejiler kullanılabilir:

1. **Çift/Tek Strateji:** Çift numaralı filozoflar önce sol çatalı, tek numaralılar önce sağ çatalı alır
2. **Kaynak Sıralaması:** Tüm filozoflar her zaman düşük numaralı çatalı önce alır
3. **Arbitrator (Garson):** Merkezi bir mutex ile aynı anda sadece N-1 filozof yemek yiyebilir

### Race Condition Önleme

- Her çatal için ayrı mutex
- Ölüm kontrolü için ayrı mutex
- Yazdırma işlemleri için ayrı mutex (çıktıların karışmaması için)

### Zaman Yönetimi

```c
// Hassas zamanlama için önerilen usleep implementasyonu
void    precise_sleep(long ms)
{
    long    start;

    start = get_time_ms();
    while ((get_time_ms() - start) < ms)
        usleep(100);
}
```

## ⚠️ Dikkat Edilmesi Gerekenler

1. **Data Race:** Paylaşılan değişkenlere erişimde mutex kullanımı zorunlu
2. **Mutex Sırası:** Lock sırası tutarlı olmalı (deadlock önleme)
3. **Bellek Sızıntısı:** Tüm mutex'ler destroy edilmeli, malloc'lar free'lenmeli
4. **Zaman Hassasiyeti:** `usleep` tam hassas değil, busy-wait ile kombinle
5. **Ölüm Kontrolü:** Monitor thread ile sürekli kontrol

## 🧪 Test Senaryoları

```bash
# Ölmemeli testler
./philo 5 800 200 200        # Standart test
./philo 4 410 200 200        # Sınır testi
./philo 2 800 200 200        # Minimum filozof

# Ölmeli testler
./philo 4 310 200 100        # Ölmeli
./philo 1 800 200 200        # Tek filozof (ölmeli - 2 çatal yok)

# Yemek sayısı testi
./philo 5 800 200 200 7      # 7 yemekten sonra durmalı
./philo 4 410 200 200 10     # 10 yemekten sonra durmalı
```

## 📚 Öğrenilen Kavramlar

- **Multithreading:** Paralel programlama temelleri
- **Mutex:** Karşılıklı dışlama mekanizması
- **Deadlock:** Kilitlenme durumu ve önleme yöntemleri
- **Race Condition:** Yarış durumu ve çözümleri
- **Starvation:** Açlık durumu (kaynak erişim adaleti)
- **Thread Senkronizasyonu:** İş parçacıkları arası koordinasyon

## 📝 Notlar

- Her filozofun kendi thread'i vardır
- Monitor thread ölüm kontrolü yapar
- Bir filozof öldüğünde tüm simülasyon durur
- Çıktı formatı: `[timestamp_in_ms] [philosopher_id] [action]`

## 📜 Çıktı Formatı

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
...
```

## 👤 Yazar

- **42 Login:** [malbayra]
- **GitHub:** [https://github.com/HalilAlb]

---

*Bu proje 42 School müfredatının bir parçasıdır.*
