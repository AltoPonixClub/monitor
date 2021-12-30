class SystemState {
   private:
      SystemState() {
      }
  public: 
    float atmosTemp = -1;
    float nutrientSolutionTemp = -1;
    float nutrientResevoirPH = -1;
    float nutrientResevoirEC = -1;
    float lightLevel = -1;
    float airFlow = -1;
    float humidity = -1;
    float dissolvedOxygen = -1;
    float mediumMoisture = -1;
    int cycleCount = -1; 
    static SystemState* GetInstance() {
      static SystemState instance;
      return &instance;
    }
};

struct PortConstants {
  // Put port constants here
};

class Commands {
  private:
    Commands() {
    }
  public:
    int dataSize = 1;
    boolean printDataCom = false;
    static Commands* GetInstance() {
      static Commands instance;
      return &instance;
    }
};

class SystemReader {
  public:
    static void Initialize(SystemState &state, Commands &commands) {
    }
    static void Update(SystemState &state, Commands &commands) {
      state.atmosTemp = GetAtmosTemp();
      state.nutrientSolutionTemp = GetNutrientSolutionTemp();
      state.nutrientResevoirPH = GetNutrientResevoirPH();
      state.nutrientResevoirEC = GetNutrientResevoirEC();
      state.lightLevel = GetLightLevel();
      state.airFlow = GetAirFlow();
      state.humidity = GetHumidity();
      state.dissolvedOxygen = GetDissolvedOxygen();
      state.mediumMoisture = GetMediumMoisture();
      String pySignal = GetPrintSignal();
      UpdateCommands(pySignal, commands);
      state.cycleCount++;
    }
    static void UpdateCommands(String sig, Commands &commands)
    {
      int strLength = 0;
      while(sig[strLength] != '\0' ){
         strLength++;
      }
      int len = 1;
      for (int i = 0; i < strLength; i++)
      {
         if (sig[i] == ',') len++;
      }
      static String ret[100];
      String temp = "";
      int index = 0;
      for (int i = 0; i < strLength; i++)
      {
         if (sig[i] == ',')
         {
           ret[index] = temp;
           temp = "";
           index ++;
         }
         else
         {
          temp += sig[i];
         }
      }
      ret[index] = temp;
      for (int i = 0; i < len; i+=2)
      {
        if (ret[i] == "printDataCom")
        {
          if (ret[i+1] == "True")
          {
            commands.printDataCom = true;
          }
        }
      }
    }
  private:
    SystemReader() {
    }
    static double GetAtmosTemp() {
      return 1.1;
    }
    static double GetNutrientSolutionTemp() {
      return 2.2;
    }
    static double GetNutrientResevoirPH() {
      return 3.3;
    }
    static double GetNutrientResevoirEC() {
      return 4.4;
    }
    static double GetLightLevel() {
      return 5.5;
    }
    static double GetAirFlow() {
      return 6.6;
    }
    static double GetHumidity() {
      return 7.7;
    }
    static double GetDissolvedOxygen() {
      return 8.8;
    }
    static double GetMediumMoisture() {
      return 9.9;
    }
    static String GetPrintSignal()
    {
      if (Serial.available())
      {
         String sig = "";
         while (true)
         {
            String tempSig = Serial.readString();
            if (tempSig == " " || tempSig == "\n")
            {
              break;
            }
            else if(tempSig == ".")
            {
              break;
            }
            else
            {
              sig += tempSig;
            }
         }
         return sig;
      }
      return " ";
    }
};

class SystemWriter {
  public:
    static void Initialize(SystemState &state, Commands &commands) {
      InitDataCom();
    }
    static void Update(SystemState &state, Commands &commands) {
      UpdateDataCom(state, commands.printDataCom);
      commands.printDataCom = false;
    }
  private:
    SystemWriter() {
    }
    static void InitDataCom() {
      // Initialize Serial Comunications
      Serial.begin(4800);
      Serial.setTimeout(0);
    }
    static void UpdateDataCom(SystemState &state, boolean printDataCom) {
      if (printDataCom) {
        String serDataCom = "";
        serDataCom += "atmospheric_temp";
        serDataCom += state.atmosTemp;
        serDataCom += ',';
        serDataCom += "reservoir_temp";
        serDataCom += state.nutrientSolutionTemp;
        serDataCom += ',';
        serDataCom += "ph";
        serDataCom += state.nutrientResevoirPH;
        serDataCom += ',';
        serDataCom += "electrical_conductivity";
        serDataCom += state.nutrientResevoirEC;
        serDataCom += ',';
        serDataCom += "light_intensity";
        serDataCom += state.lightLevel;
        serDataCom += ',';
        serDataCom += "air_flow";
        serDataCom += state.airFlow;
        serDataCom += ',';
        serDataCom += "dissolved_oxygen";
        serDataCom += state.dissolvedOxygen;
        serDataCom += ',';
        serDataCom += "soil_moisture";
        serDataCom += state.mediumMoisture;
        Serial.println(serDataCom);
      }
      else
      {
        Serial.println("No Data");
      }
    }
};

SystemState state = *(SystemState::GetInstance());
Commands commands = *(Commands::GetInstance());

void setup() {
  SystemReader::Initialize(state, commands);
  SystemWriter::Initialize(state, commands);
}

void loop() {
  SystemReader::Update(state, commands);
  SystemWriter::Update(state, commands);
}
