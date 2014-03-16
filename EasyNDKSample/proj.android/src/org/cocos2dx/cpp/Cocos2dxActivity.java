package org.cocos2dx.cpp;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;

import com.easyndk.classes.AndroidNDKHelper;

// The name of .so is specified in AndroidMenifest.xml. NativityActivity will load it automatically for you.
// You can use "System.loadLibrary()" to load other .so files.

public class Cocos2dxActivity extends NativeActivity {

	static {
		System.loadLibrary("jansson");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		//For supports translucency

		//1.change "attribs" in cocos\2d\platform\android\nativeactivity.cpp
		/*const EGLint attribs[] = {
	            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	            //EGL_BLUE_SIZE, 5,   -->delete
	            //EGL_GREEN_SIZE, 6,  -->delete
	            //EGL_RED_SIZE, 5,    -->delete
	            EGL_BUFFER_SIZE, 32,  //-->new field
	            EGL_DEPTH_SIZE, 16,
	            EGL_STENCIL_SIZE, 8,
	            EGL_NONE
	    };*/

		//2.Set the format of window
		// getWindow().setFormat(PixelFormat.TRANSLUCENT);

		/* Let the helper know that this class wants to receive data from your game */
		AndroidNDKHelper.SetNDKReceiver(this);
	}

	/* Your method must have this JSONObject parameter */
	public void nativeTestMethod(JSONObject parameters) {
		if (parameters != null) {
			try {
				String testMessage = parameters.getString("test_message");
				double pi = parameters.getDouble("test_double");

				Log.i("Message received from game", testMessage);
				Log.i("Value of test double", String.valueOf(pi));

				/* Let's send a message back to the game */
				JSONObject message = new JSONObject();
				JSONArray numbersArray = new JSONArray();

				try {
					numbersArray.put(1);
					numbersArray.put(1);
					numbersArray.put(2);
					numbersArray.put(3);
					numbersArray.put(5);
					numbersArray.put(8);

					message.put("test_response", "Greetings from Android!");
					message.put("fibonacci", numbersArray);
				} catch (JSONException e) {
					e.printStackTrace();
				}

				// Send C++ a message with parameters
				// C++ will receive this message only if the selector list has a method
				// of the same name as specified - in this case, "gameTestMethod"
				AndroidNDKHelper.SendMessageWithParameters("gameTestMethod", message);
			} catch (JSONException e) {
				e.printStackTrace();
			}
		}
	}
}
