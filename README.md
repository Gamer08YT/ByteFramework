# ByteFramework

ByteFramework is a lightweight, modular web framework that allows you to create an interactive web interface in just a
few steps - without any in-depth frontend knowledge. Ideal for prototypes, dashboards, admin panels or quick MVPs.

## How to install

PlatformIO
Registry: [https://registry.platformio.org/libraries/bytestore/ByteFramework](https://registry.platformio.org/libraries/bytestore/ByteFramework)

    - Use: `lib_deps=bytestore/ByteFramework` to point to latest version
    - Use: `lib_deps=bytestore/ByteFramework@^<x.y.z>` to point to latest version with the same major version
    - Use: `lib_deps=bytestore/ByteFramework@<x.y.z>` to always point to the same version (reproductible build)

lib_deps=bytestore/ByteFramework

### How does listeners work?

Each component or DOM element has a fixed ID; if a listener is registered on it, it is triggered via the Page Route →
Component ID → Event Type.

### Can the frontend currently be updated?

Unfortunately no frontend manipulation is possible at the moment, but I plan to implement a small workaround via
“eval()” and yes I know **"EVAL is evil"** 😈

### Are Sessions supported yet?

Currently there is no authentication system that allows user sessions or permissions, I am happy about any support.

### How does the Communication work?

In my frameworks I normally use a hybrid that supports both XHR polling and WebSockets, but since I only have a limited
flash capacity on the ESP, I only use WebSockets, which should be supported by every modern browser.