## Soil Sensor Node V2.

The Soil Sensor Node is a device designed to monitor and analyze soil condi􀆟ons in agricultural and
environmental applications.

### Install the application after first clone.

Run the following.
```bash
git clone https://github.com/tatware/gateway_node_v2.git
cd gateway_node_v2
git submodule update --init --recursive
cd esp-idf\
install.bat 
cd ..
cd gateway 
cd components\arduino\tools
python get.py
```
### Compile and flash the project.

Run the following.
```bash
cd esp-idf\
export.bat
cd ..                   
cd gateway or cd node             # Go to the project directory
idf.py build            # Compile the Project  
idf.py -p PORT flash    # Flash the Project
```

### Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

