# Enchanted-Penholder
Image
## Final project for Physical computing class
The enchanted penholder measures and displays indoor environmental conditions in addition to ... yes ... holding pens and pencils. The device is equiped with sensors to measure temperature, air flow, CO2, light levels and background sound. Its modularity allows additional sensors to be afixed to it - for example, CO, PM 2.5, VOCs. 

To a building occupant who spends up to half the day at their workstation, this information is useful because their environment has impacts on their health, productivity, comfort and happiness. For the occupant to have this information is a liability to the building owner but also a compulsion to better buildings.

To a facilities manager, the enchanted penholder provides a granular feedback of building conditions. Where previously, the feedback was per building zone, it can now be per workstation without instrusion into the occupant's work schedule. Equiped with this information, the facilities manager can more easily localize problems in mechanical systems, for example where exactly the light fittings have failed, or where high levels of CO2 indicate a defective ventilator.

To a building performance evaluator, records of data collected by the enchanted penholder would save time (which would otherwise be spent collecting the same data and only then for a short period of time) yet give a better picture of environmental conditions. Qualitative surveys of occupant perceptions could be taken and stored together with the measurements making a comprehensive evaluation of the indoor conditions possible.

## The Device
The idea behind the device was to take an existing device in the usual ensemble of a typical office worker and equip it with sensing capabilities, thus the enchanted penholder. The sensors are built into modules that connect to a particle photon microprocessor that is permanently installed into the device. The photon runs an upgradable code for the sensors. Modularity of the sensor boxes allows customization of the data collection to any parameters of choice. Modularity allows for expansion or even reduction of modules.

The current device configuration contains 6 modules and a penholder section that is rounded at the front with a living hinge. The modules and frame are porous to expose the sensors to the air circulation as much as possible. The six modules are:
1. a screen to display the values of each parameter
2. a light sensor module with a transparent top surface
3. a CO2 unit - though the CO2 sensor was not used since it could not fit into the module
4. a background sound sensor module
5. an air flow sensor module
6. a temperature module which shares the same sensor with the air flow module. In the temperature module is an indicator light to alert the occupant when the temperature exceeds a recommended threshold. Such an alert indicator would be integrated into each of the sensor modules.

## Data Visualization
The enchanted penholder transmits the collected data through particle's publish feature to an online database - [ThingSpeak](https://thingspeak.com/). The data is presented in graphical form.
Background Sound Display

## Precedents
The closest similarity to the enchanted penholder is an indoor environmental quality measurement device used for post occupancy evaluation by a team of University of South California researchers. Their device (image below) was purposely built for the exercise. It was handed out to occupants at the start of the experiment and retrieved afterwards. It more compact and is not meant to be an ambient device.
Similar Indoor measurement device
