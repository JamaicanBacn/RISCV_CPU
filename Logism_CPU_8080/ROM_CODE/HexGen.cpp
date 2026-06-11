/*
    Hex code generator for Logism Evolution ROM flashing

    Instruction set:

        LDA 
        LDB
        ADD
        SUB
        OUT
        JMP

*/

#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<fstream>


void ROM_segment_display_programmer(std::ofstream& ROM , int dig);
void Double_encoded_Display_rom( std::ofstream& ROM , int upper , int digit);
void ROM_Fetch_Decode_Programmer( std::ofstream& ROM , std::ofstream& ROM2);

void ROM_LDA(std::ofstream& ROM , std::ofstream& ROM2);
void ROM_LDB(std::ofstream& ROM , std::ofstream& ROM2);
void ROM_LDI(std::ofstream& ROM , std::ofstream& ROM2);

void ROM_STA(std::ofstream& ROM , std::ofstream& ROM2);
void ROM_STB(std::ofstream& ROM , std::ofstream& ROM2);

void ROM_ADD(std::ofstream& ROM , std::ofstream& ROM2);
void ROM_SUB(std::ofstream& ROM , std::ofstream& ROM2);

void ROM_JMP(std::ofstream& ROM , std::ofstream& ROM2);
void ROM_HLT(std::ofstream& ROM , std::ofstream& ROM2);
void ROM_OUT(std::ofstream& ROM , std::ofstream& ROM2);


std::string decimal_hex_codes[16] = {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};



int main()
{

    // Programming each decimal place for the rom files

    /*

    std::ofstream ones("ones.txt");
    std::ofstream tens("tens.txt");
    std::ofstream huns("huns.txt");
    std::ofstream thou("thou.txt");
    std::ofstream tthou("tthou.txt");

    ROM_segment_display_programmer(ones  , 0);
    ROM_segment_display_programmer(tens  , 1);
    ROM_segment_display_programmer(huns  , 2);
    ROM_segment_display_programmer(thou  , 3);
    ROM_segment_display_programmer(tthou , 4);


    ones.close();
    tens.close();
    huns.close();
    thou.close();
    tthou.close();

    */

    // programming the roms for the control unit

    std::ofstream Instruction_Rom1("Instruction_Rom1.txt");
    std::ofstream Instruction_Rom2("Instruction_Rom2.txt");

    ROM_Fetch_Decode_Programmer(Instruction_Rom1 , Instruction_Rom2);

    ROM_LDA(Instruction_Rom1,Instruction_Rom2);
    ROM_LDB(Instruction_Rom1,Instruction_Rom2);
    ROM_LDI(Instruction_Rom1,Instruction_Rom2);

    ROM_STA(Instruction_Rom1,Instruction_Rom2);
    ROM_STB(Instruction_Rom1,Instruction_Rom2);

    ROM_ADD(Instruction_Rom1,Instruction_Rom2);
    ROM_SUB(Instruction_Rom1,Instruction_Rom2);

    ROM_JMP(Instruction_Rom1,Instruction_Rom2);
    ROM_OUT(Instruction_Rom1,Instruction_Rom2);
    ROM_HLT(Instruction_Rom1,Instruction_Rom2);

    Instruction_Rom1.close();
    Instruction_Rom2.close();

    

    return 1;


}

void ROM_segment_display_programmer(std::ofstream& ROM , int dig)
 {
    /*
    
    The first 65536 contain the ones place for each number combination
    This pattern continues so each place in the rom plus 2^16+i contains the digit for the i+1 place

    */
    
    int max_val = 65535;

    Double_encoded_Display_rom(ROM , max_val , pow( 10 , dig));
   
 }

void Double_encoded_Display_rom( std::ofstream& ROM , int upper , int digit)

 // largest 2 comp number : 32767
 // smallest 2 comp number : 32768


 {
    for(int i = 0; i <= upper; i++)
    {
        if(i < 32768 )
        {
            ROM << decimal_hex_codes[(i / digit ) % 10] + decimal_hex_codes[( i /digit ) % 10] + '\n';
        }
        else{
            ROM << decimal_hex_codes[(i / digit ) % 10] + decimal_hex_codes[( ( upper - i + 1 )/ digit ) % 10] + '\n';
        }
    }
 }

void ROM_Fetch_Decode_Programmer( std::ofstream& ROM , std::ofstream& ROM2)
{
    /*
    
        Programs the fetch decode cycle by placing the fetch decode at each possible
        instruction location that has the stepper at adress 0
    
    */
    for(int i = 0; i < 16; i++)
    {
        ROM  << decimal_hex_codes[i] + "0: 40 \n";    // PC out
        ROM  << decimal_hex_codes[i] + "1: 14 \n";
        ROM2 << decimal_hex_codes[i] + "0: 04 \n";    // PC Mar in
        ROM2 << decimal_hex_codes[i] + "1: 08 \n";
        
    }

}

void ROM_LDA(std::ofstream& ROM , std::ofstream& ROM2 )
{
    ROM << "12: 48 \n";
    ROM << "13: 12 \n"; 
}

void ROM_LDB(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM  << "22: 48 \n";
    ROM  << "23: 10 \n";
    ROM2 << "23: 20 \n"; 
}

void ROM_STA(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM << "32: 48\n";
    ROM << "33: 21\n";
}

void ROM_STB(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM  << "42: 48 \n";
    ROM  << "43: 20 \n";
    ROM2 << "43: 01 \n";  
}

void ROM_ADD(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM  << "52: 02 \n";
    ROM2 << "52: 80 \n";
}

void ROM_SUB(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM  << "62: 02 \n";
    ROM2 << "62: c0 \n";
}

void ROM_JMP(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM  << "d2: 08 \n";
    ROM2 << "d2: 02 \n"; 
}

void ROM_LDI(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM << "c2: 0a \n";
}

void ROM_HLT(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM << "e2: 80 \n";
}

void ROM_OUT(std::ofstream& ROM , std::ofstream& ROM2)
{
    ROM  << "f2: 01 \n";
    ROM2 << "f2: 10 \n";
}


