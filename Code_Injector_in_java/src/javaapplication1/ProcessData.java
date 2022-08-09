/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package javaapplication1;

import java.awt.Component;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Stream;
import javax.swing.JFileChooser;
import javax.swing.JProgressBar;
import javax.swing.filechooser.FileSystemView;

/**
 *
 * @author ezequeil
 */
public class ProcessData {
    
    private static File fileSave;
    private static String data_file;
    private boolean is_check;
    private long size, index;
    
    public File openFile(Component parent){
    
        JFileChooser jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
        int returnValue = jfc.showOpenDialog(parent);   // ****
       // iFRAME.dispose();
        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File selectedFile = jfc.getSelectedFile();
            return (selectedFile);
        }
        return (null);
    }
    
    private long getSize(String fileNameOpen){
    
        long s;
       
        FileReader fileReader;
        try {
            fileReader = new FileReader(fileNameOpen);
        } catch (FileNotFoundException ex) {
            return (0);
        }
        s = 0;
         try (BufferedReader bufferedReader = new BufferedReader(fileReader)) {
                s = bufferedReader.lines().count();
            bufferedReader.close();
            fileReader.close();
        } catch (IOException ex) {
            Logger.getLogger(ProcessData.class.getName()).log(Level.SEVERE, null, ex);
        }
        return s;
    }
    
    public void read_write(FileReader fileReader, File  fileWrite, String txt_applaer, JProgressBar bar, String fileNameOpen)
    {
        bar.setValue(0);
        try {
            try (BufferedReader bufferedReader = new BufferedReader(fileReader); FileWriter save = new FileWriter(fileWrite)) {
                    Stream<String> lines = bufferedReader.lines();
                    size = getSize(fileNameOpen);
                    bar.setMaximum((int)size);
                    lines.forEach(line ->
                    {
                        bar.setValue(bar.getValue() + 1);
                        checkData(line);
                        checkValue(save, line, txt_applaer);
                        try {
                            save.write(line + "\n");
                        } catch (IOException ex) {
                            Logger.getLogger(ProcessData.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                );
                 bar.setValue(bar.getMaximum());
                 System.out.println("save: ok ");
                if (fileReader != null)
                    fileReader.close();
                bufferedReader.close();
            }
           
        } catch (FileNotFoundException ex) {
            Logger.getLogger(ProcessData.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(ProcessData.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    private void checkData(String line){
        
        if (!line.contains("<WorkDate>"))
            return;
        line =  line.replace("<WorkDate>", "");
        line = line.replace("</WorkDate>", "");
        data_file = line.trim();
    }
    
    private void checkValue(FileWriter save, String line, String txt)
    {
        
        if (is_check && line.contains("  <DocumentTotals>"))
        {
            txt = txt.replace("value_data", data_file);
            try {
                save.write(txt);
                save.write("\n");
            } catch (IOException ex) {}
        }
        is_check = false;
        if (line.contains("<CustomerID>999999</CustomerID>"))
             is_check = true;
    }

}