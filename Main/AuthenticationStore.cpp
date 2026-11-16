#include "AuthenticationStore.h"

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QFileDevice>
#include <QFileInfo>
#include <QRegularExpression>
#include <QStringList>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace {
constexpr int SaltLength = 16;
constexpr int HashLength = 32;
constexpr int Pbkdf2Iterations = 310000;

