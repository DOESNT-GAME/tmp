// sha384.cpp
#include "sha384.h"
#include <array>
#include <algorithm>
#include <cstring>
#include <vector>
#include <QByteArray>

namespace {

// Константы для SHA-384
constexpr std::array<uint64_t, 8> initialHash = {
    0xcbbb9d5dc1059ed8ULL, 0x629a292a367cd507ULL, 0x9159015a3070dd17ULL,
    0x152fecd8f70e5939ULL, 0x67332667ffc00b31ULL, 0x8eb44a8768581511ULL,
    0xdb0c2e0d64f98fa7ULL, 0x47b5481dbefa4fa4ULL
};

constexpr std::array<uint64_t, 80> k = {
    0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
    0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
    0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
    0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
    0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
    0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
    0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
    0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
    0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
    0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
    0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
    0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
    0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
    0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
    0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
    0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
    0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
    0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};

// Вспомогательные функции для SHA-384
inline uint64_t rotr64(uint64_t x, uint64_t n) { return (x >> n) | (x << (64 - n)); }
inline uint64_t ch(uint64_t x, uint64_t y, uint64_t z) { return (x & y) ^ (~x & z); }
inline uint64_t maj(uint64_t x, uint64_t y, uint64_t z) { return (x & y) ^ (x & z) ^ (y & z); }
inline uint64_t sigma0(uint64_t x) { return rotr64(x, 28) ^ rotr64(x, 34) ^ rotr64(x, 39); }
inline uint64_t sigma1(uint64_t x) { return rotr64(x, 14) ^ rotr64(x, 18) ^ rotr64(x, 41); }
inline uint64_t gamma0(uint64_t x) { return rotr64(x, 1) ^ rotr64(x, 8) ^ (x >> 7); }
inline uint64_t gamma1(uint64_t x) { return rotr64(x, 19) ^ rotr64(x, 61) ^ (x >> 6); }
}

QString SHA384::hash(const QString& input)
{
    // Преобразуем строку в UTF-8 байты
    QByteArray message = input.toUtf8();
    const uint8_t* msg = reinterpret_cast<const uint8_t*>(message.constData());
    uint64_t length = message.size();

    // Инициализация хеш-значений
    std::array<uint64_t, 8> hash = initialHash;

    // Подготовка сообщения с дополнением
    uint64_t bitLength = length * 8;
    uint64_t newLength = ((((length + 16) / 128) + 1) * 128) - 1;
    std::vector<uint8_t> paddedMessage(newLength + 1, 0);
    std::memcpy(paddedMessage.data(), msg, length);
    paddedMessage[length] = 0x80;

    // Добавляем длину сообщения в битах в конец (big-endian)
    for (int i = 0; i < 8; ++i) {
        paddedMessage[newLength - 7 + i] = (bitLength >> (8 * (7 - i))) & 0xFF;
    }

    // Обработка сообщения блоками по 1024 бита (128 байт)
    for (uint64_t i = 0; i < paddedMessage.size(); i += 128) {
        std::array<uint64_t, 80> w = {0};

        // Разбиваем блок на 16 слов по 64 бита (big-endian)
        for (int t = 0; t < 16; ++t) {
            for (int j = 0; j < 8; ++j) {
                w[t] = (w[t] << 8) | paddedMessage[i + t * 8 + j];
            }
        }

        // Расширяем первые 16 слов в остальные 64 слова
        for (int t = 16; t < 80; ++t) {
            w[t] = gamma1(w[t-2]) + w[t-7] + gamma0(w[t-15]) + w[t-16];
        }

        // Инициализация рабочих переменных
        uint64_t a = hash[0], b = hash[1], c = hash[2], d = hash[3];
        uint64_t e = hash[4], f = hash[5], g = hash[6], h = hash[7];

        // Основной цикл сжатия
        for (int t = 0; t < 80; ++t) {
            uint64_t t1 = h + sigma1(e) + ch(e, f, g) + k[t] + w[t];
            uint64_t t2 = sigma0(a) + maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        // Обновляем хеш-значения
        hash[0] += a; hash[1] += b; hash[2] += c; hash[3] += d;
        hash[4] += e; hash[5] += f; hash[6] += g; hash[7] += h;
    }

    // Формируем итоговый хеш (первые 384 бита = 6 слов по 64 бита)
    QByteArray result;
    for (int i = 0; i < 6; ++i) {
        for (int j = 7; j >= 0; --j) {
            result.append(static_cast<char>((hash[i] >> (8 * j)) & 0xFF));
        }
    }

    return QString(result.toHex());
}
