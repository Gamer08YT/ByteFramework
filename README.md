# ByteFramework

ByteFramework is a lightweight, modular web framework that allows you to create an interactive web interface in just a
few steps - without any in-depth frontend knowledge. Ideal for prototypes, dashboards, admin panels or quick MVPs.

### How does listeners work?
Each component or DOM element has a fixed ID; if a listener is registered on it, it is triggered via the Page Route → Component ID → Event Type.

### Are Sessions supported yet?

Currently there is no authentication system that allows user sessions or permissions, I am happy about any support.

### How does the Communication work?

In my frameworks I normally use a hybrid that supports both XHR polling and WebSockets, but since I only have a limited
memory capacity on the ESP, I only use WebSockets, which should be supported by every modern browser.