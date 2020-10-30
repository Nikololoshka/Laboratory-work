#ifndef CRYPTOWRAPPER_H
#define CRYPTOWRAPPER_H

#include <windows.h>
#include <QtCore>


class CryptoWrapper
{
public:
    CryptoWrapper(const QString &passphrase);
    ~CryptoWrapper();

    QString encrypt(const QString &text);
    QString decrypt(const QString &text);

private:
    [[noreturn]] void error(const std::string &msg);

private:
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    BYTE *bpMode;
};

#endif // CRYPTOWRAPPER_H
