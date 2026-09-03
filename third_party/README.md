# Third-party component status

The directories in this location are reference or porting placeholders and are
not selectable firmware components:

| Component | Status |
| --- | --- |
| cJSON | Placeholder API; parsing and printing are not implemented |
| SEGGER RTT | Minimal study stub; not validated as the upstream component |
| lwIP | Architecture headers only; protocol sources and network interface missing |
| EasyLogger | Public header only; source and port layer missing |
| Letter Shell | Documentation/build placeholders only; source missing |

These options were intentionally removed from Kconfig and CMake. A component
must contain pinned upstream source, license, platform port and tests before it
can be exposed as a selectable feature.
