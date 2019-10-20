#include <Config/Config.hpp>

#include <Util/Hash.hpp>

#include <cstdio>

#include <openssl/sha.h>

namespace Knock {

namespace Hash { // Knock::Hash
namespace NoCheck { // Knock::Hash::NoCheck

std::string bufferSha256( const void* pBuf, size_t bufSize )
{
    unsigned char hash[ Knock::Hash::Sha256DigestLength ];

    ::SHA256_CTX sha256;
    ::SHA256_Init( &sha256 );
    ::SHA256_Update( &sha256, pBuf, bufSize );
    ::SHA256_Final( hash, &sha256 );

    std::string result( Knock::Hash::Sha256DigestLength * 2, '\0' );
    for ( size_t i = 0; i < Knock::Hash::Sha256DigestLength; ++i ) {
        sprintf( const_cast<char*>( result.data() + i * 2 ), "%02x", hash[ i ] );
    }

    return result;
}

} // Knock::Hash::NoCheck

void sha256_string(const char *string, char outputBuffer[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

std::string fileSha256( const boost::filesystem::path& filePath )
{
    std::ifstream in( filePath.string(), std::ios::binary );
    std::vector<unsigned char> v( std::istreambuf_iterator<char>{ in }, {} );
    return bufferSha256( v );
}

std::string bufferSha256( const std::vector<unsigned char>& buf )
{
    if ( buf.empty() ) {
        return "";
    }

    return NoCheck::bufferSha256( buf.data(), buf.size() );
}

std::string bufferSha256( const void* pBuf, size_t bufSize )
{
    if ( nullptr == pBuf || 0 == bufSize ) {
        return "";
    }

    return NoCheck::bufferSha256( pBuf, bufSize );
}

} // Knock::Hash
} // Knock