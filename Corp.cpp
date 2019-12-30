#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <sstream>
#include <bitset>

using namespace std;

int main (int argc, char** argv) {
	ifstream config;
	config.open(argv[1]);

	int m, k;
	config >> m >> k;

	config.close();

	ofstream out;
	string out_file_name = string(argv[2]) + ".out";
	out.open(out_file_name.c_str());

	ifstream trace;
	trace.open(argv[2]);
	unsigned long pc; bool taken;
	trace >> std::hex >> pc >> taken;


	int breadth = (int) pow(2,k);
    int depth = (int) pow(2,m);
    //cout<<depth<<endl;
    //cout<<breadth<<endl;

    //create predictor arrays
    int corp[depth][breadth];

    //initialize to 1

    for(int a = 0;a<=depth;a++)
    {   for(int b = 0;b<=breadth;b++)
    {
    corp[a][b] = 11;
    }
    }
    int bhr[k];
    for(int br=0;br<k;br++)
    {
    bhr[br] = 1;
    }

    stringstream brhiscomp;
    int posd,posb;
    //1 = T , 0 = NT


	while (!trace.eof()) {

        for(int br=0;br<k;br++)
        {
        brhiscomp<<bhr[br];
        }

        bitset<32> pcb(pc);

        posb = (int)bitset<32>(brhiscomp.str()).to_ulong();
        posd = (int)bitset<32>(pcb.to_string().substr(32-m,m)).to_ulong();

		bool prediction;
		int predictor;
		predictor = corp[posd][posb];

		if(predictor == 11 || predictor == 10)
            {
             prediction = true;

             if(taken == false)
                {
                 if (predictor == 11)
                    {
                     corp[posd][posb] = 10;
                    }
                 if (predictor == 10)
                    {
                     corp[posd][posb] = 00;
                    }
                }
              if(taken == true)
                {
                 if (predictor == 10)
                    {
                     corp[posd][posb] = 11;
                    }
                }

             }

            if(predictor == 00 || predictor == 01)
            {
             prediction = false;

                if(taken == true)
                    {
                    if (predictor == 00)
                        {
                        corp[posd][posb] = 01;
                        }
                    if (predictor == 01)
                        {
                        corp[posd][posb] = 11;
                        }
                    }
                if(taken == false)
                    {
                    if (predictor == 01)
                    {
                     corp[posd][posb] = 00;
                    }
                }

             }

        for(int br=0;br<k-1;br++)
        {
        bhr[br+1] = bhr[br];
        }

        bhr[0] = (int)taken;

        brhiscomp.str("");

		out << prediction<<endl;
		trace >> std::hex >> pc >> taken;
	}

	trace.close();
	out.close();
}
