#include "sendframe.h"

SendFrame::SendFrame()
{
}


void SendFrame::config_buffer()
{


    for (int i = 0 ; i < 17 ; i++)
    {
        char_array[i] = 0;
    }

    int char_array_index = 0; //0
    if (frame[0] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128;}
    if (frame[1] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;}
    if (frame[2] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;}
    if (frame[3] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;}
    if (frame[4] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8; }
    if (frame[5] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4; }
    if (frame[6] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2; }
    if (frame[7] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1; }

    char_array_index = char_array_index + 1; //1
    if (frame[8] == '1'  )  {char_array[char_array_index] = char_array[char_array_index] | 128;  }
    if (frame[9] == '1'  )  {char_array[char_array_index] = char_array[char_array_index] | 64;   }
    if (frame[10] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[11] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[12] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[13] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[14] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[15] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;   }

    char_array_index = char_array_index + 1; //2
    if (frame[16] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128;  }
    if (frame[17] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;   }
    if (frame[18] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;   }
    if (frame[19] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;   }
    if (frame[20] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;    }
    if (frame[21] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;    }
    if (frame[22] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;    }
    if (frame[23] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;    }

    char_array_index = char_array_index + 1; //3
    if (frame[24] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[25] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[26] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[27] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[28] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[29] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[30] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[31] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 1;   }

    char_array_index = char_array_index + 1; //4
    if (frame[32] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128;  }
    if (frame[33] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;   }
    if (frame[34] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;   }
    if (frame[35] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;   }
    if (frame[36] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;    }
    if (frame[37] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;    }
    if (frame[38] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;    }
    if (frame[39] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;    }

    char_array_index = char_array_index + 1; //5
    if (frame[40] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[41] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[42] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[43] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[44] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[45] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[46] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[47] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 1;   }

    char_array_index = char_array_index + 1; //6
    if (frame[48] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128;  }
    if (frame[49] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;   }
    if (frame[50] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;   }
    if (frame[51] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;   }
    if (frame[52] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;    }
    if (frame[53] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;    }
    if (frame[54] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;    }
    if (frame[55] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;    }

    char_array_index = char_array_index + 1; //7
    if (frame[56] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[57] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[58] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[59] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[60] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[61] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[62] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[63] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;   }

    char_array_index = char_array_index + 1; //8
    if (frame[64] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128;  }
    if (frame[65] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;   }
    if (frame[66] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;   }
    if (frame[67] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;   }
    if (frame[68] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;    }
    if (frame[69] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;    }
    if (frame[70] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;    }
    if (frame[71] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;    }

    char_array_index = char_array_index + 1; //9
    if (frame[72] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[73] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[74] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[75] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[76] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[77] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[78] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[79] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;   }
    //--------------------------------------------------------------------------------------------
    char_array_index = char_array_index + 1; //10
    if (frame[80] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[81] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[82] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[83] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[84] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[85] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[86] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[87] == '1' )  { char_array[char_array_index] = char_array[char_array_index] | 1;   }

    char_array_index = char_array_index + 1; //11
    if (frame[88] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128;  }
    if (frame[89] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;   }
    if (frame[90] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;   }
    if (frame[91] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;   }
    if (frame[92] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;    }
    if (frame[93] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;    }
    if (frame[94] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;    }
    if (frame[95] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;    }

    char_array_index = char_array_index + 1; //12
    if (frame[96] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[97] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[98] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[99] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[100] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[101] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[102] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[103] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;   }

    char_array_index = char_array_index + 1; //13
    if (frame[104] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128;  }
    if (frame[105] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;   }
    if (frame[106] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;   }
    if (frame[107] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;   }
    if (frame[108] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;    }
    if (frame[109] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;    }
    if (frame[110] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;    }
    if (frame[111] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;    }

    char_array_index = char_array_index + 1; //14
    if (frame[112] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[113] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[114] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[115] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[116] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[117] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[118] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[119] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;   }

    char_array_index = char_array_index + 1; //15
    if (frame[120] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 128; }
    if (frame[121] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 64;  }
    if (frame[122] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 32;  }
    if (frame[123] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 16;  }
    if (frame[124] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 8;   }
    if (frame[125] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 4;   }
    if (frame[126] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 2;   }
    if (frame[127] == '1' ) { char_array[char_array_index] = char_array[char_array_index] | 1;   }
    //--------------------------------------------------------------------------------------------




}
