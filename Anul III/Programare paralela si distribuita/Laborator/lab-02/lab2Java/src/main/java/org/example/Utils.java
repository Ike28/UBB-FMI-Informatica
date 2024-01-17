package org.example;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class Utils {
    public void generareMatrice(int n, int m, int min, int max, String fileName){
        try {
            FileWriter writer = new FileWriter(fileName);
            Random random = new Random();
            for(int i = 0; i < n; i ++){
                for (int j = 0; j < m; j ++) {
                    int value = random.nextInt(max-min) + min;
                    writer.write(value + " ");
                }
                writer.write("\n");
            }
            writer.close();
        }
        catch(IOException exception){
            exception.printStackTrace();
        }
    }

    public boolean equalResults(String fname1, String fname2){

        try {
            File fd1 = new File(fname1);
            File fd2 = new File(fname2);
            if(fd1.length() != fd2.length())
                return false;
            Scanner fs1 = new Scanner(fd1);
            Scanner fs2 = new Scanner(fd2);
            while(fs1.hasNextInt())
                if(fs1.nextInt() != fs2.nextInt())
                    return false;
            fs1.close();
            fs2.close();
            return true;
        }
        catch(IOException exception){
            exception.printStackTrace();
        }
        return false;
    }
}
