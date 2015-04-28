struct PerformanceTestSetup
{
	unsigned	ClientsStartCount;
	unsigned	ClientsNewByTick;
	unsigned	ObjectsStartCount;
	unsigned	ObjectsNewByTick;
	unsigned	NetworkUpdateLimitInMs;
	unsigned	TimeToWasteInMs;
	unsigned	RunOnlyLimitInMs;
	unsigned	TimeoutLimitInMs;
	unsigned	ThreadCount;
	float		ObjectChangeQuotaInPercent;
	float		ClientChangeQuotaInPercent;
	float		ClientNeedObjectQuotaInPercent;

	PerformanceTestSetup(void)
		: ClientsStartCount(1), ClientsNewByTick(0), ObjectsStartCount(0), ObjectsNewByTick(0),
		  NetworkUpdateLimitInMs(10), TimeToWasteInMs(50), RunOnlyLimitInMs(10000), TimeoutLimitInMs(600000),
		  ThreadCount(0), ObjectChangeQuotaInPercent(1), ClientChangeQuotaInPercent(1), ClientNeedObjectQuotaInPercent(1) {}
};

class PerformanceTest : public helpers::ThreadedObject
{
	bool running;
	unsigned StartTime;
	unsigned LastInsert;
	TestServer server;
	TestObject root;
	std::list<TestClient*> clientlist;
	PerformanceTestSetup Setup;

	bool ShouldStop(void) const { return !running; }

	bool DoCreations(unsigned acttime);
	void ThreadUpdate(unsigned);

public:
	PerformanceTest(PerformanceTestSetup& setup);

	void run(void);

	size_t GetObjectCount(void) const { return server.GetObjectCount(); }
	size_t GetClientCount(void) const { return clientlist.size(); }
};

std::ostream& operator << (std::ostream& off, const PerformanceTestSetup& t);
