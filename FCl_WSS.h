#ifndef FCl_WSSH
#define FCl_WSSH

#include "OverbyteIcsWndControl.hpp"
#include "OverbyteIcsWSocket.hpp"
#include "OverbyteIcsWSocketS.hpp"
#include "Unit2.h"
#include <vector>
#include <DBXJSON.hpp>

class TLogic;

class TClient: public TSslWSocketClient
{
public:
String Rcvd;
TWSocket* RemoteSocket;
inline __fastcall ~TClient(void);
};

class TServer : public TSslWSocketServer
{
typedef TWSocketServer inherited;
public:
UnicodeString LocalPort;
UnicodeString RemotePort;
UnicodeString RemoteIP;
UnicodeString RemoteAddress;
UnicodeString OurLogin;
TLog* ServerLog;
TLogic* ServerLogic;
inline __fastcall virtual TServer(System::Classes::TComponent* AOwner) : TSslWSocketServer(AOwner) { }
void inline __fastcall Init(UnicodeString LocalPort,UnicodeString RemotePort,UnicodeString RemoteIP,UnicodeString RemoteAddress,UnicodeString OurLogin);
void __fastcall WSocketServerClientConnect(TObject *Sender, TWSocketClient *Client, WORD Error);
void __fastcall RemoteSessionConnected(TObject *Sender, WORD Error);
void __fastcall RemoteDataAvailable(TObject *Sender, WORD Error);
void __fastcall ClientDataAvailable(TObject *Sender, WORD Error);
void __fastcall RemoteSessionClosed(TObject *Sender, WORD Error);
void __fastcall BgException(TObject *Sender, Exception *E, bool &CanClose);
UnicodeString __fastcall ExchangeString(UnicodeString In);
void __fastcall SetLogLevel(short);
inline __fastcall virtual ~TServer(void) { }
};

enum Version {cm91z = 0, cm93z_pl, cm74et};
class TLogic
{
public:
Version minerVersion;
std::vector<UnicodeString>* Pools;
short LogLevel;//NAU//0 - not, 1 - short, 2 - full
std::vector<UnicodeString>* Methods;

TLogic();
TLogic(int);
void UpdateSettings(int);
void SetServerLogic(TServer*);

~TLogic();
};
#endif
