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
                console.log('Connected to WebSocket server');
            };

            this.ws.onmessage = (event) => {
                try {
                    const data = JSON.parse(event.data);

                    switch (data.type) {
                        case 'config':
                            this.maxReconnectAttempts = data.value.maxReconnectAttempts;
                            this.reconnectDelay = data.value.reconnectDelay;
                            break;
                        case 'welcome':
                            // Register Listeners.
                            console.log('Welcome message received');
                            console.log(data.value);
                            break;
                        case 'eval':
                            // I know EVAL is bad ;)
                            eval(data.value);
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