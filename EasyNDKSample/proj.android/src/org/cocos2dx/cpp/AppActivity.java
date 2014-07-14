/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.os.Bundle;
import android.util.Log;

import com.easyndk.classes.AndroidNDKHelper;

public class AppActivity extends Cocos2dxActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

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
