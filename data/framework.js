/**
 * Framework class facilitates establishing and managing a WebSocket connection
 * to a server, with automatic reconnection capabilities. It listens for specific
 * message types to handle configuration updates or execute server-provided commands.
 */
class Framework {
    ws = null;
    isConnected = false;
    reconnectAttempts = 0;
    maxReconnectAttempts = 5;
    reconnectDelay = 3000;

    /**
     * Initializes a new instance of the class and establishes a WebSocket connection
     * to the server using the current hostname.
     *
     * @return {void} This constructor does not return a value.
     */
    constructor() {
        this.connect("ws://${window.location.hostname}/ws");
    }

    /**
     * Sends a packet of data over a WebSocket connection.
     * The packet is formatted as a JSON string with the specified type and value.
     *
     * @param {string} type The type of the packet to be sent.
     * @param {*} value The value associated with the packet.
     * @return {void} This method does not return any value.
     */
    sendPacket(type, value) {
        const packet = JSON.stringify({
            "type": type,
            "value": value
        });

        this.ws.send(packet);

        console.log('Sent packet:', packet);
    }

    /**
     * Establishes a WebSocket connection to the specified URL.
     *
     * @param {string} url - The URL of the WebSocket server to connect to.
     * @return {void}
     */
    connect(url) {
        try {
            this.ws = new WebSocket(url);

            this.ws.onopen = () => {
                this.isConnected = true;
                this.reconnectAttempts = 0;

                // Request Welcome Packet.
                this.sendPacket("navigate", {
                    "route": window.location.pathname
                });

                console.log('Connected to WebSocket server');
            };

            this.ws.onmessage = (event) => {
                try {
                    const data = JSON.parse(event.data);
                    const value = data.value;

                    // Switch through incoming packets.
                    switch (data.type) {
                        case 'config':
                            this.maxReconnectAttempts = value.maxReconnectAttempts;
                            this.reconnectDelay = value.reconnectDelay;
                            break;
                        case 'welcome':
                            // Register Listeners.
                            console.log('Welcome message received');
                            console.log(value);
                            break;
                        case 'message':
                            console.log(value.message);
                            break;
                        case 'eval':
                            // I know EVAL is bad ;)
                            eval(value.value);
                            break;
                        case 'ping':
                            this.ws.send('pong');
                            break;
                    }

                    console.log('Received data:', data);
                } catch (error) {
                    console.error('Error parsing message:', error);
                }
            };

            this.ws.onerror = (error) => {
                console.error('WebSocket error:', error);
            };

            this.ws.onclose = () => {
                this.isConnected = false;
                console.log('WebSocket connection closed');
                this.reconnect(url);
            };

        } catch (error) {
            console.error('Connection error:', error);
            this.reconnect(url);
        }
    }

    /**
     * Attempts to reconnect to the specified URL if the maximum number of reconnection attempts has not been reached.
     * Each reconnection attempt is delayed by a specified timeout.
     *
     * @param {string} url - The URL to which the reconnection should be attempted.
     * @return {void} This method does not return a value.
     */
    reconnect(url) {
        if (this.reconnectAttempts < this.maxReconnectAttempts) {
            this.reconnectAttempts++;
            console.log(`Reconnecting... Attempt ${this.reconnectAttempts} of ${this.maxReconnectAttempts}`);

            setTimeout(() => {
                this.connect(url);
            }, this.reconnectDelay);
        } else {
            console.error('Max reconnection attempts reached');
        }
    }

}

new Framework();