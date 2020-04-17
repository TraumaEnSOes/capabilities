#include <algorithm>
#include <functional>
#include <iostream>

static void countingSort( char *begin, const char *end ) {
  unsigned char results[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  for( auto iter = begin; iter != end; ++iter ) {
    ++( results[*iter - ' '] );
  }

  for( unsigned char idx = 0; idx < ( sizeof( results ) / sizeof( results[1] ) ); ++idx ) {
    unsigned char &count = results[idx];
    while( count ) {
      char value = idx + ' ';
      *begin = value;
      ++begin;
      --count;
    }
  }
}

static char *reverseWords( const char *str ) {
    struct WordInfo {
    size_t length;
    const char *begin;

    WordInfo( const char *str ) :
      length( 0 )
    {
      while( *str && *str <= ' ' ) { ++str; }
      if( !( *str ) ) { return; }

      begin = str;

      while( *str && *str > ' ' ) {
        ++str;
        ++length;
      }
    }
  };

  if( !str ) { return nullptr; }

  char *result;
  char *writer;
  std::function< void( const char *, size_t ) > recursive = [&result, &writer, &recursive]( const char *str, size_t acu ) -> void {
    WordInfo wi( str );

    // No hay mas palabras.
    if( !wi.length ) {
      result = new char[acu + 1];
      writer = result;

      return;
    }

    auto inc = wi.length;
    if( acu ) { ++inc; }

    recursive( wi.begin + wi.length, acu + inc );
    
    auto spaceIter = std::copy( wi.begin, wi.begin + wi.length, writer );
    countingSort( writer, writer + wi.length );

    if( acu ) {
      *spaceIter = ' ';
      ++spaceIter;
    }

    writer = spaceIter;
  };

  recursive( str, 0 );

  return result;
}

int main( ) {
  const char *origen = "   el    cielo     esta enladrillado     ";
  const char *reverse = reverseWords( origen );

  std::cout << '{' << origen << "}\n";
  std::cout << '{' << reverse << "}\n";

  return 0;
}
