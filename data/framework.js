class Framework {
    ws = null;
    isConnected = false;
    reconnectAttempts = 0;
    maxReconnectAttempts = 5;
    reconnectDelay = 3000;

    constructor() {

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