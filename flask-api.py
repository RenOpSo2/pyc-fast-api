from flask import Flask, render_template, jsonify
import ctypes
import os

app = Flask(__name__)

lib = ctypes.CDLL('./runtime/core.so')

lib.process_request.argtypes = []
lib.process_request.restype = ctypes.c_char_p
lib.get_server_info.argtypes = []
lib.get_server_info.restype = ctypes.c_char_p

@app.route("/")
def home():
    info = lib.get_server_info()
    return render_template('index.html', 
                          title="High Performance Flask-C API",
                          info=info.decode('utf-8'))

@app.route("/api/data")
def get_data():
    result = lib.process_request()
    return jsonify({
        "status": "success",
        "message": "data processed in C for maximum speed",
        "data": result.decode('utf-8'),
        "performance": "fast"
    })

@app.route("/api/health")
def health_check():
    return jsonify({
        "status": "healthy",
        "runtime": "Flask + C Native",
        "performance": "optimized"
    })

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000, debug=False, threaded=True)
