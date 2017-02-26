/*
    Copyright (C) 2003 Justin Karneges <justin@affinix.com>
    Copyright (C) 2005-2006 Brad Hards <bradh@frogmouth.net>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// QtCrypto has the declarations for all of QCA
#include <QtCrypto>
#include <stdio.h>

#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QCA::Initializer init;
    QCA::SecureArray arg = (argc >= 2) ? argv[1] : "hello";

    QCA::SymmetricKey key(16);
    QCA::InitializationVector iv(16);

    QCA::Cipher cipher(QString("aes256"),QCA::Cipher::CBC);
    cipher.setup( QCA::Encode, key, iv );

    QCA::SecureArray u = cipher.update(arg);
    QCA::SecureArray f = cipher.final();

    printf("Final block for AES128 encryption is [0x%s]\n", qPrintable(QCA::arrayToHex(f.toByteArray())) );

    cipher.setup( QCA::Decode, key, iv );

    QCA::SecureArray cipherText = u.append(f);

    QCA::SecureArray plainText = cipher.update(cipherText);
    plainText = cipher.final();

    printf("Final decryption block using AES128 is %s\n", plainText.data());

    QCA::SymmetricKey key2(16);
    QCA::Cipher cipher2(QString("aes256"),QCA::Cipher::CBC);
    cipher2.setup( QCA::Decode, key, iv );
    QCA::SecureArray plainText2 = cipher2.update(cipherText);
    plainText2 = cipher2.final();

    printf("One step decryption using AES128: %s\n",
            plainText2.data() );

    return 0;
}
