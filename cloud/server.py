from flask import Flask, request, jsonify
from datetime import datetime

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    data = request.get_json()

    log = {
        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        "temperature": data.get("temperature"),
        "humidity": data.get("humidity"),
        "soil_moisture": data.get("soil_moisture"),
        "alert": data.get("alert")
    }

    print("📡 Data Received from ESP32:")
    print(log)
    print("-" * 40)

    return jsonify({
        "status": "success",
        "message": "Data received successfully"
    }), 200


if __name__ == '__main__':
    print("🚀 IoT Agriculture Server Started")
    print("📍 Listening on all network interfaces (0.0.0.0:5000)")
    app.run(host='0.0.0.0', port=5000, debug=True)
