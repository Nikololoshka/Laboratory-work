#include "cryptoWrapper.h"
#include <wincrypt.h>
#include <string.h>
#include <iostream>

using namespace std;

CryptoWrapper::CryptoWrapper(const QString &passphrase)
{
    // Инициализация контекста
    if(!CryptAcquireContext(
            &hProv,             // 1 - дескриптор провайдера
            NULL,               // 2 - имя контейнера ключей
            NULL,               // 3 - имя провайдера (по умолчанию)
            PROV_RSA_AES,       // 4 - тип провайдера (симметричный)
            CRYPT_VERIFYCONTEXT // 5 - флаги
            )
        ) {
        qDebug() << NTE_BAD_KEYSET;
        error("init context");
    }

    // Создание пустого хеш-объекта
    if (!CryptCreateHash(
            hProv,
            CALG_MD4,
            NULL,
            NULL,
            &hHash)
        ) {
        error("create hash");
    }

    auto stdPassphase = passphrase.toStdString();
    const CHAR *password = stdPassphase.c_str();
    DWORD length = (DWORD) strlen(password);

    // Хеширование парольной фразы
    if (!CryptHashData(
            hHash,
            (BYTE *) password,
            length,
            NULL
            )
        ) {
        error("hash data");
    }

    // Создание ключа
    if (!CryptDeriveKey(
            hProv,
            CALG_RC2,
            hHash,
            CRYPT_EXPORTABLE | CRYPT_CREATE_SALT ,
            &hKey
            )
        ) {
        error("derive key");
    }

    DWORD dwMode = CRYPT_MODE_ECB;
    bpMode = new BYTE(CRYPT_MODE_ECB);

    // Установка режима шифрования
    if (!CryptSetKeyParam(
            hKey,
            KP_MODE,
            (BYTE*) &dwMode,
            NULL
            )
        ) {
        error("set key param");
    }
}


CryptoWrapper::~CryptoWrapper()
{
    CryptReleaseContext(hProv, NULL);
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);
}

QString CryptoWrapper::encrypt(const QString &text)
{
    string value = text.toStdString();

    size_t batchSize = 8;
    size_t batchCount = value.size() / batchSize;
    if (value.size() % batchSize != 0) {
        ++batchCount;
    }

    std::string encrypt;

    size_t i = 0;
    while (true) {
        bool isEnd = i >= (batchCount - 1);

        std::string substr = !isEnd ? value.substr(i * batchSize, batchSize)
                                    : value.substr(i * batchSize);

        const char *data = substr.c_str();
        DWORD len = strlen(data);

        // шифрование порции данных из буфера pbData
        if (!CryptEncrypt(hKey, NULL, isEnd, NULL, (BYTE *) data, &len, batchSize)) {
            error("CryptEncrypt");
        }

        encrypt += data;

        if (isEnd) {
            break;
        }

        ++i;
    }

    return QLatin1String(encrypt.c_str());
}

QString CryptoWrapper::decrypt(const QString &text)
{
    string value = text.toLatin1().toStdString();

    size_t batchSize = 8;
    size_t batchCount = value.size() / batchSize;
    if (value.size() % batchSize != 0) {
        ++batchCount;
    }

    std::string decrypt;


    size_t i = 0;
    while (true) {
        bool isEnd = i >= (batchCount - 1);

        std::string substr = !isEnd ? value.substr(i * batchSize, batchSize)
                                    : value.substr(i * batchSize);

        const char *data = substr.c_str();
        DWORD len = DWORD(strlen(data));

        // cout << data << " " << isEnd << endl;

        // расшифрование порции данных из буфера pbData
        if (!CryptDecrypt(hKey, NULL, isEnd, NULL, (BYTE *) data, &len)) {
            return QString(decrypt.c_str());
            // error("CryptDecrypt");
        }

        // cout << "Data: " << data << ", " << len << endl;
        auto temp = std::string(data).substr(0, len);
        decrypt += temp;


        if (isEnd) {
            break;
        }

        ++i;
    }

    return QString(decrypt.c_str());
}

void CryptoWrapper::error(const string &msg)
{
    qDebug() << "Failed " << QString::fromStdString(msg) << ", code: " << GetLastError() << endl;
    throw std::runtime_error("Unknow error");
}

