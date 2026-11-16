// Deletable_Java_File_Do_Not_Remove_String
package org.firstinspires.ftc.teamcode.opmodes;

import android.util.Log;

import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.eventloop.opmode.TeleOp;

import org.firstinspires.ftc.robotcore.internal.system.AppUtil;

@TeleOp(name = "<class_name>", group = "<group_name>")
public class <class_name> extends LinearOpMode {
    static
    {
        String dir = AppUtil.getInstance().getActivity().getApplicationInfo().nativeLibraryDir;
        Log.i("DIR", dir);
        System.load(dir + "/libc++_shared.so");
        System.load(dir + "/libsdk_loader.so");
    }

    public native void <class_name>();

    @Override
    public void runOpMode()
    {
        <class_name>();
    }
}