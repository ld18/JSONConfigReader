# JSONConfigReader
Simple jason configuration reader for a text file based software configuration

Simple little parser which allows to fetch values from a config json.
It is thread safe and fail-fast written (there a get functions with default values).

Values can be accessed via a template function with a path of keys separated by '/'

    cr.get<int>("Peak_Detector/arr/2")
    // JASON file
    // "Peak_Detector":{
    //  "arr": [
    //    1,
    //...

In branch Examples is an example project.

Based on the JASON Parser from gregjesl (https://github.com/gregjesl/simpleson)
