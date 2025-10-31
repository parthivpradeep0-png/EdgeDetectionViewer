package com.example.edgedetectionviewer

import android.graphics.BitmapFactory
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView
import android.widget.TextView
import java.io.File
import java.io.FileOutputStream

class MainActivity : AppCompatActivity() {

    external fun stringFromJNI(): String
    external fun detectEdges(imagePath: String): String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val textView = findViewById<TextView>(R.id.sample_text)
        val imageView = findViewById<ImageView>(R.id.imageView)

        // ✅ Copy a sample drawable image into app cache
        val inputStream = resources.openRawResource(R.drawable.sample)
        val inputFile = File(cacheDir, "input.jpg")
        FileOutputStream(inputFile).use { output ->
            inputStream.copyTo(output)
        }

        // ✅ Call native (C++) functions
        val msg = stringFromJNI()
        val result = detectEdges(inputFile.absolutePath)

        // ✅ Show status messages
        textView.text = "$msg\n$result"

        // ✅ Try loading the generated edges image
        val outputFile = File(cacheDir, "edges.jpg")
        if (outputFile.exists()) {
            val bmp = BitmapFactory.decodeFile(outputFile.absolutePath)
            imageView.setImageBitmap(bmp)
        } else {
            textView.append("\n⚠️ Output image not found!")
        }
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}





