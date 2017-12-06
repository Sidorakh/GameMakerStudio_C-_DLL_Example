
# Guide for doing things!

## Writing C++ code for use in GameMaker Studio extensions

To start, we will define a macro in C++, to make our lives easier. 
```cpp
#define dllx extern "C" __declspec(dllexport)
```
Defining a function using this (the macro `dllx` in this case) is telling the compiler to allow an external program to use this function (your GameMaker projects, in this case). 

To demonstrate this, we will write a very basic function that takes three numbers and returns the total. 

```cpp
dllx double addThreeNumbers(double a, double b, double c) {
    return a+b+c;
}
```

## Adding the functions in GameMaker Studio 1.x
<p align="center">
	<img src="https://i.imgur.com/3vQiM63.png">
</p>
Right click the file and select Add Function

<p align="center">
	<img src="https://i.imgur.com/bpkTcZs.png">
</p>
Properly defining the function within GameMkaer Studio


## Returning DS Maps from a DLL
There are two methods to achieve this. The furst is the simplest, to return the map directly from the external function, while the second is to call an async event and access the map through `async_load`

Before starting these, you wil need to add the following code to your `main.cpp` file

```cpp
//define functions
void (*CreateAsynEventWithDSMap)(int,int) = NULL;
int (*CreateDsMap)(int _num, ... ) = NULL;
bool (*DsMapAddDouble)(int _index,char *_pKey,double value)=NULL;
bool (*DsMapAddString)(int _index, char *_pKey, char *pVal)=NULL;

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

```

Then, you'll need to add a function to the DLL called RegisterCallbacks. Needs to have four arguments (each a string). Return type should be left as double. This function is automatically called by GameMaker when defined correctly, and is used to set up the DS Map creation functions.
![Registering function](https://i.imgur.com/ecUdI0T.png)

