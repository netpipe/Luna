struct PerformanceTestSetup;

class TestObject : public syncsys::NetEntity, public helpers::ThreadedObject
{
	const PerformanceTestSetup*	Setup;
	volatile unsigned			LastInsert;
	bool						Run;

	void FillObject(void);
	void Serialize(syncsys::NetAction, helpers::NetworkBuffer&);
	void Deserialize(syncsys::NetAction, helpers::NetworkBuffer&);

public:
	std::list<TestObject*> SubObjects;

	double	blub1;
	char	blub2;
	float	blub3;
	int		blub4;
	bool	blub5;
	char	blub6[100];

	TestObject(syncsys::NetIDManager* e, const  PerformanceTestSetup* = 0);
	TestObject(syncsys::NetEntity* e, bool TakeClientListFromElement);
	TestObject(syncsys::NetEntity* e, const PerformanceTestSetup&, bool ThreadObject = false);
	TestObject(const syncsys::ContainerConnector& c, syncsys::SyncClient* cli, bool dodeserialize);
	~TestObject();

	syncsys::NetActionFlag ClientNeedsUpdates(syncsys::SyncServerClient* client);
	void ThreadUpdate(unsigned acttime);
	void Update(unsigned acttime);
	void Update(unsigned acttime, const syncsys::ChangedClientContainer &in)	{ AddClients(in); Update(acttime); }
	void CreateSubObjects(unsigned count);

	bool ShouldStop(void) const { return !Run; }

	unsigned GetLastInsertTimeInMs(void) const { return LastInsert; }
};

class TestClient : public syncsys::SyncClient
{
public:

};

class TestServerClient :public syncsys::SyncServerClient
{
	unsigned int	RefCounter;
	float			ClientChangeQuotaInPercent;

	~TestServerClient()	{}

public:
	TestClient*		Client;

	TestServerClient( TestClient* _Client, float _ClientChangeQuotaInPercent, unsigned short StartUpdateMsg = 0)
		: syncsys::SyncServerClient(StartUpdateMsg), RefCounter(1), ClientChangeQuotaInPercent(_ClientChangeQuotaInPercent), Client(_Client) {}

	void Update(bool updatedirectly);
	void grab(void)						{ helpers::Atomic_Inc(RefCounter); }
	void drop(void)						{ if(0 == helpers::Atomic_Dec(RefCounter)) delete this; }
	bool IsKicked(void) const			{ return (Client == 0); }
};

class TestServer : public syncsys::NetIDManager
{
public:
	std::list<TestServerClient*>	clientlist;

	TestServerClient* AddClient(TestClient* c, float QuotaToChangeInPercent);
	void RemoveClient(TestClient* c, bool onlysetpointer = true);
	void UpdateClients(bool updateclientobjectsdirectly);
	void ClearClientList(void);

	TestServer();
	~TestServer();

	size_t GetObjectCount(void) const	{ return Elemente.size(); }
};
