package com.example.nativeapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.nativeapplication.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private var socket = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        //Connect to server
        socket = connect("192.168.83.202", 8900)

        //Send data to server
        sendData(socket, "This my first NDK programme")

        //Collected data from server
        var collectedData = receivedData(socket)

        binding.sampleText.text = collectedData

        //Close the the server connection
        disconnect(socket)

    }

    /**
     * A native method that is implemented by the 'nativeapplication' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun connect(ip: String, port: Int): Int
    external fun disconnect(socket: Int)
    external fun receivedData(socket: Int): String
    external fun sendData(socket: Int, data:String)

    companion object {
        // Used to load the 'nativeapplication' library on application startup.
        init {
            System.loadLibrary("nativeapplication")
        }
    }
}