# rmw_gurumdds
Implementation of the ROS middleware interface using [GurumNetworks GurumDDS](http://www.gurum.cc).

## Requirements
Required version of GurumDDS depends on the version of this project.

| rmw_gurumdds            | GurumDDS                    |
|-------------------------|-----------------------------|
| 1.1.1 or higher         | 2.8.x                       |
| 1.0.3 or higher         | 2.7.x                       |
| 1.0.2 or lower          | 2.6.x(deprecated)           |

## Packages
This project consists of four packages, `gurumdds_camke_module`, `rmw_gurumdds_cpp`, `rmw_gurumdds_shared_cpp` and `demo_nodes_cpp_native_gurumdds`.

### gurumdds_cmake_module
`gurumdds_cmake_module` looks for GurumDDS, and provides the information to other packages.  
For `gurumdds_cmake_module` to work properly, you need to set `GURUMDDS_HOME` environment variable to where GurumDDS is located.  
For example, if you set `GURUMDDS_HOME=~/gurumdds`, the directory `~/gurumdds` should look like this:
```
gurumdds
├── gurumdds.lic
├── gurumdds.yaml
├── examples
│   └── ...
├── include
│   └── gurumdds
│       ├── dcps.h
│       ├── dcpsx.h
│       ├── typesupport.h
│       └── xml.h
├── lib
│   └── libgurumdds.so
├── Makefile
└── tool
    └── gurumidl
```

### rmw_gurumdds_cpp
`rmw_gurumdds_cpp` is the rmw implementation. You can use this rmw implementation by setting environment variable `RMW_IMPLEMENTATION=rmw_gurumdds_cpp` after installation. For `rmw_gurumdds_cpp` to work properly, make sure to set environment variable `GURUMDDS_CONFIG=$GURUMDDS_HOME/gurumdds.yaml` and set `allow_loopback` variable in `gurumdds.yaml` to `true`. If you are not familiar with [YAML](https://yaml.org/), please note that YAML only supports spaces, not tabs, for indentation.  

```
DATA:
  allow_loopback: true
  dynamic_buffer: true
  mtu: auto # auto | number(1472)
  bitmap_capacity: 256
  buffer_capacity: 512
```

<<<<<<< HEAD
### rmw_gurumdds_static_cpp
`rmw_gurumdds_static_cpp` is another rmw implementation, which uses `rosidl_typesupport_gurumdds`, our own typesupport packages. You can use this rmw implementation with environment variable `RMW_IMPLEMENTATION=rmw_gurumdds_static_cpp`. Other settings and configurations are the same as `rmw_gurumdds_cpp`.  
This package is disabled by default.

=======
>>>>>>> f08ee60... Reorganize package
### rmw_gurumdds_shared_cpp
`rmw_gurumdds_shared_cpp` contains some functions used by `rmw_gurumdds_cpp`.

### demo_nodes_cpp_native_gurumdds
`demo_nodes_cpp_natvie_gurumdds` is similar to `demo_nodes_cpp_native` from ROS2 `demos`. This demo shows how to access the native handles of `rmw_gurumdds_cpp`.  
This package is disabled by default.

## Branches
There are three active branches in this project: master, galactic and foxy.
New changes made in [ROS2 repository](https://github.com/ros2) will be applied to the master branch, so this branch might be unstable.
If you want to use this project with ROS2 Rolling Ridley or Galactic Geochelone, please use master or galactic branch, respectively.

## Implementation Status
Currently some features are not fully implemented.
- DDS Security
