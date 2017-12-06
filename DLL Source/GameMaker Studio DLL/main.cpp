//Macro to define all options for DLL exporting
#define dllx extern "C" __declspec(dllexport)

// ID for the social async event
const int EVENT_OTHER_SOCIAL = 70;

// defines function pointers for the DS map creation
void (*CreateAsynEventWithDSMap)(int,int) = NULL;
int (*CreateDsMap)(int _num, ... ) = NULL;
bool (*DsMapAddDouble)(int _index,char *_pKey,double value)=NULL;
bool (*DsMapAddString)(int _index, char *_pKey, char *pVal)=NULL;

// Simple function definition
dllx double addThreeNumbers(double a, double b, double c) {
    // A very simple function to start with
    return a+b+c;
}

// Required for async events to fire properly
dllx RegisterCallbacks(char *arg1, char *arg2, char *arg3, char *arg4) {
    void (*CreateAsynEventWithDSMapPtr)(int,int) = (void (*)(int,int))(arg1);
    int(*CreateDsMapPtr)(int _num,...) = (int(*)(int _num,...)) (arg2);
    CreateAsynEventWithDSMap = CreateAsynEventWithDSMapPtr;
    CreateDsMap = CreateDsMapPtr;

    bool (*DsMapAddDoublePtr)(int _index,char *_pKey,double value)= (bool(*)(int,char*,double))(arg3);
    bool (*DsMapAddStringPtr)(int _index, char *_pKey, char *pVal)= (bool(*)(int,char*,char*))(arg4);

    DsMapAddDouble = DsMapAddDoublePtr;
    DsMapAddString = DsMapAddStringPtr;
}

// Simple DS Map creation
dllx double CreateDsMapStandard(char *key, double value) {
    int newMap = CreateDsMap(0);
    DsMapAddDouble(newMap,key,value);
    // you can just return a ds map if you want!
    return (double)newMap;
}

// Simple DS Map creation with an async return
dllx double CreateDsMapAsync(char *key, double value) {
    int newMap = CreateDsMap(0);
    DsMapAddDouble(newMap,key,value);
    // the new event is added here!
    CreateAsynEventWithDSMap(newMap, EVENT_OTHER_SOCIAL);
    return 0.0;
}


