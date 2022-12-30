/* @file CustomKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates changing the keypad size and key values.
  || #
*/
#include "BigKeypad.h"

uint16_t gobanLegend[19][19] = {
  {'AA', 'AB', 'AC', 'AD', 'AE', 'AF', 'AG', 'AH', 'AI', 'AJ', 'AK', 'AL', 'AM', 'AN', 'AO', 'AP', 'AQ', 'AR', 'AS'},
  {'BA', 'BB', 'BC', 'BD', 'BE', 'BF', 'BG', 'BH', 'BI', 'BJ', 'BK', 'BL', 'BM', 'BN', 'BO', 'BP', 'BQ', 'BR', 'BS'},
  {'CA', 'CB', 'CC', 'CD', 'CE', 'CF', 'CG', 'CH', 'CI', 'CJ', 'CK', 'CL', 'CM', 'CN', 'CO', 'CP', 'CQ', 'CR', 'CS'},
  {'DA', 'DB', 'DC', 'DD', 'DE', 'DF', 'DG', 'DH', 'DI', 'DJ', 'DK', 'DL', 'DM', 'DN', 'DO', 'DP', 'DQ', 'DR', 'DS'},
  {'EA', 'EB', 'EC', 'ED', 'EE', 'EF', 'EG', 'EH', 'EI', 'EJ', 'EK', 'EL', 'EM', 'EN', 'EO', 'EP', 'EQ', 'ER', 'ES'},
  {'FA', 'FB', 'FC', 'FD', 'FE', 'FF', 'FG', 'FH', 'FI', 'FJ', 'FK', 'FL', 'FM', 'FN', 'FO', 'FP', 'FQ', 'FR', 'FS'},
  {'GA', 'GB', 'GC', 'GD', 'GE', 'GF', 'GG', 'GH', 'GI', 'GJ', 'GK', 'GL', 'GM', 'GN', 'GO', 'GP', 'GQ', 'GR', 'GS'},
  {'HA', 'HB', 'HC', 'HD', 'HE', 'HF', 'HG', 'HH', 'HI', 'HJ', 'HK', 'HL', 'HM', 'HN', 'HO', 'HP', 'HQ', 'HR', 'HS'},
  {'IA', 'IB', 'IC', 'ID', 'IE', 'IF', 'IG', 'IH', 'II', 'IJ', 'IK', 'IL', 'IM', 'IN', 'IO', 'IP', 'IQ', 'IR', 'IS'},
  {'JA', 'JB', 'JC', 'JD', 'JE', 'JF', 'JG', 'JH', 'II', 'JJ', 'JK', 'JL', 'JM', 'JN', 'JO', 'JP', 'JQ', 'JR', 'JS'},
  {'KA', 'KB', 'KC', 'KD', 'KE', 'KF', 'KG', 'KH', 'KI', 'KJ', 'KK', 'KL', 'KM', 'KN', 'KO', 'KP', 'KQ', 'KR', 'KS'},
  {'LA', 'LB', 'LC', 'LD', 'LE', 'LF', 'LG', 'LH', 'LI', 'LJ', 'LK', 'LL', 'LM', 'LN', 'LO', 'LP', 'LQ', 'LR', 'LS'},
  {'MA', 'MB', 'MC', 'MD', 'ME', 'MF', 'MG', 'MH', 'MI', 'MJ', 'MK', 'ML', 'MM', 'MN', 'MO', 'MP', 'MQ', 'MR', 'MS'},
  {'NA', 'NB', 'NC', 'ND', 'NE', 'NF', 'NG', 'NH', 'NI', 'NJ', 'NK', 'NL', 'NM', 'NN', 'NO', 'NP', 'NQ', 'NR', 'NS'},
  {'OA', 'OB', 'OC', 'OD', 'OE', 'OF', 'OG', 'OH', 'OI', 'OJ', 'OK', 'OL', 'OM', 'ON', 'OO', 'OP', 'OQ', 'OR', 'OS'},
  {'PA', 'PB', 'PC', 'PD', 'PE', 'PF', 'PG', 'PH', 'PI', 'PJ', 'PK', 'PL', 'PM', 'PN', 'PO', 'PP', 'PQ', 'PR', 'PS'},
  {'QA', 'QB', 'QC', 'QD', 'QE', 'QF', 'QG', 'QH', 'QI', 'QJ', 'QK', 'QL', 'QM', 'QN', 'QO', 'QP', 'QQ', 'QR', 'QS'},
  {'RA', 'RB', 'RC', 'RD', 'RE', 'RF', 'RG', 'RH', 'RI', 'RJ', 'RK', 'RL', 'RM', 'RN', 'RO', 'RP', 'RQ', 'RR', 'RS'},
  {'SA', 'SB', 'SC', 'SD', 'SE', 'SF', 'SG', 'SH', 'SI', 'SJ', 'SK', 'SL', 'SM', 'SN', 'SO', 'SP', 'SQ', 'SR', 'SS'}
};

uint16_t gobanLegend2[19][19] = {
  {'AA', 'AB', 'AC', 'AD', 'AE', 'AF', 'AG', 'AH', 'AJ', 'AK', 'AL', 'AM', 'AN', 'AO', 'AP', 'AQ', 'AR', 'AS', 'AT'},
  {'BA', 'BB', 'BC', 'BD', 'BE', 'BF', 'BG', 'BH', 'BJ', 'BK', 'BL', 'BM', 'BN', 'BO', 'BP', 'BQ', 'BR', 'BS', 'BT'},
  {'CA', 'CB', 'CC', 'CD', 'CE', 'CF', 'CG', 'CH', 'CJ', 'CK', 'CL', 'CM', 'CN', 'CO', 'CP', 'CQ', 'CR', 'CS', 'CT'},
  {'DA', 'DB', 'DC', 'DD', 'DE', 'DF', 'DG', 'DH', 'DJ', 'DK', 'DL', 'DM', 'DN', 'DO', 'DP', 'DQ', 'DR', 'DS', 'DT'},
  {'EA', 'EB', 'EC', 'ED', 'EE', 'EF', 'EG', 'EH', 'EJ', 'EK', 'EL', 'EM', 'EN', 'EO', 'EP', 'EQ', 'ER', 'ES', 'ET'},
  {'FA', 'FB', 'FC', 'FD', 'FE', 'FF', 'FG', 'FH', 'FJ', 'FK', 'FL', 'FM', 'FN', 'FO', 'FP', 'FQ', 'FR', 'FS', 'FT'},
  {'GA', 'GB', 'GC', 'GD', 'GE', 'GF', 'GG', 'GH', 'GJ', 'GK', 'GL', 'GM', 'GN', 'GO', 'GP', 'GQ', 'GR', 'GS', 'GT'},
  {'HA', 'HB', 'HC', 'HD', 'HE', 'HF', 'HG', 'HH', 'HJ', 'HK', 'HL', 'HM', 'HN', 'HO', 'HP', 'HQ', 'HR', 'HS', 'HT'},
  {'JA', 'JB', 'JC', 'JD', 'JE', 'JF', 'JG', 'JH', 'JJ', 'JK', 'JL', 'JM', 'JN', 'JO', 'JP', 'JQ', 'JR', 'JS', 'JT'},
  {'KA', 'KB', 'KC', 'KD', 'KE', 'KF', 'KG', 'KH', 'KJ', 'KK', 'KL', 'KM', 'KN', 'KO', 'KP', 'KQ', 'KR', 'KS', 'KT'},
  {'LA', 'LB', 'LC', 'LD', 'LE', 'LF', 'LG', 'LH', 'LJ', 'LK', 'LL', 'LM', 'LN', 'LO', 'LP', 'LQ', 'LR', 'LS', 'LT'},
  {'MA', 'MB', 'MC', 'MD', 'ME', 'MF', 'MG', 'MH', 'MJ', 'MK', 'ML', 'MM', 'MN', 'MO', 'MP', 'MQ', 'MR', 'MS', 'MT'},
  {'NA', 'NB', 'NC', 'ND', 'NE', 'NF', 'NG', 'NH', 'NJ', 'NK', 'NL', 'NM', 'NN', 'NO', 'NP', 'NQ', 'NR', 'NS', 'NT'},
  {'OA', 'OB', 'OC', 'OD', 'OE', 'OF', 'OG', 'OH', 'OJ', 'OK', 'OL', 'OM', 'ON', 'OO', 'OP', 'OQ', 'OR', 'OS', 'OT'},
  {'PA', 'PB', 'PC', 'PD', 'PE', 'PF', 'PG', 'PH', 'PJ', 'PK', 'PL', 'PM', 'PN', 'PO', 'PP', 'PQ', 'PR', 'PS', 'PT'},
  {'QA', 'QB', 'QC', 'QD', 'QE', 'QF', 'QG', 'QH', 'QJ', 'QK', 'QL', 'QM', 'QN', 'QO', 'QP', 'QQ', 'QR', 'QS', 'QT'},
  {'RA', 'RB', 'RC', 'RD', 'RE', 'RF', 'RG', 'RH', 'RJ', 'RK', 'RL', 'RM', 'RN', 'RO', 'RP', 'RQ', 'RR', 'RS', 'RT'},
  {'SA', 'SB', 'SC', 'SD', 'SE', 'SF', 'SG', 'SH', 'SJ', 'SK', 'SL', 'SM', 'SN', 'SO', 'SP', 'SQ', 'SR', 'SS', 'ST'},
  {'TA', 'TB', 'TC', 'TD', 'TE', 'TF', 'TG', 'TH', 'TJ', 'TK', 'TL', 'TM', 'TN', 'TO', 'TP', 'TQ', 'TR', 'TS', 'TT'}
};

const uint16_t gobanLegend3[19][19] = {
  {0x4141, 0x4142, 0x4143, 0x4144, 0x4145, 0x4146, 0x4147, 0x4148, 0x4149, 0x414A, 0x414B, 0x414C, 0x414D, 0x414E, 0x414F, 0x4150, 0x4151, 0x4152, 0x4153},
  {0x4241, 0x4242, 0x4243, 0x4244, 0x4245, 0x4246, 0x4247, 0x4248, 0x4249, 0x424A, 0x424B, 0x424C, 0x424D, 0x424E, 0x424F, 0x4250, 0x4251, 0x4252, 0x4253},
  {0x4341, 0x4342, 0x4343, 0x4344, 0x4345, 0x4346, 0x4347, 0x4348, 0x4349, 0x434A, 0x434B, 0x434C, 0x434D, 0x434E, 0x434F, 0x4350, 0x4351, 0x4352, 0x4353},
  {0x4441, 0x4442, 0x4443, 0x4444, 0x4445, 0x4446, 0x4447, 0x4448, 0x4449, 0x444A, 0x444B, 0x444C, 0x444D, 0x444E, 0x444F, 0x4450, 0x4451, 0x4452, 0x4453},
  {0x4541, 0x4542, 0x4543, 0x4544, 0x4545, 0x4546, 0x4547, 0x4548, 0x4549, 0x454A, 0x454B, 0x454C, 0x454D, 0x454E, 0x454F, 0x4550, 0x4551, 0x4552, 0x4553},
  {0x4641, 0x4642, 0x4643, 0x4644, 0x4645, 0x4646, 0x4647, 0x4648, 0x4649, 0x464A, 0x464B, 0x464C, 0x464D, 0x464E, 0x464F, 0x4650, 0x4651, 0x4652, 0x4653},
  {0x4741, 0x4742, 0x4743, 0x4744, 0x4745, 0x4746, 0x4747, 0x4748, 0x4749, 0x474A, 0x474B, 0x474C, 0x474D, 0x474E, 0x474F, 0x4750, 0x4751, 0x4752, 0x4753},
  {0x4841, 0x4842, 0x4843, 0x4844, 0x4845, 0x4846, 0x4847, 0x4848, 0x4849, 0x484A, 0x484B, 0x484C, 0x484D, 0x484E, 0x484F, 0x4850, 0x4851, 0x4852, 0x4853},
  {0x4941, 0x4942, 0x4943, 0x4944, 0x4945, 0x4946, 0x4947, 0x4948, 0x4949, 0x494A, 0x494B, 0x494C, 0x494D, 0x494E, 0x494F, 0x4950, 0x4951, 0x4952, 0x4953},
  {0x4A41, 0x4A42, 0x4A43, 0x4A44, 0x4A45, 0x4A46, 0x4A47, 0x4A48, 0x4949, 0x4A4A, 0x4A4B, 0x4A4C, 0x4A4D, 0x4A4E, 0x4A4F, 0x4A50, 0x4A51, 0x4A52, 0x4A53},
  {0x4B41, 0x4B42, 0x4B43, 0x4B44, 0x4B45, 0x4B46, 0x4B47, 0x4B48, 0x4B49, 0x4B4A, 0x4B4B, 0x4B4C, 0x4B4D, 0x4B4E, 0x4B4F, 0x4B50, 0x4B51, 0x4B52, 0x4B53},
  {0x4C41, 0x4C42, 0x4C43, 0x4C44, 0x4C45, 0x4C46, 0x4C47, 0x4C48, 0x4C49, 0x4C4A, 0x4C4B, 0x4C4C, 0x4C4D, 0x4C4E, 0x4C4F, 0x4C50, 0x4C51, 0x4C52, 0x4C53},
  {0x4D41, 0x4D42, 0x4D43, 0x4D44, 0x4D45, 0x4D46, 0x4D47, 0x4D48, 0x4D49, 0x4D4A, 0x4D4B, 0x4D4C, 0x4D4D, 0x4D4E, 0x4D4F, 0x4D50, 0x4D51, 0x4D52, 0x4D53},
  {0x4E41, 0x4E42, 0x4E43, 0x4E44, 0x4E45, 0x4E46, 0x4E47, 0x4E48, 0x4E49, 0x4E4A, 0x4E4B, 0x4E4C, 0x4E4D, 0x4E4E, 0x4E4F, 0x4E50, 0x4E51, 0x4E52, 0x4E53},
  {0x4F41, 0x4F42, 0x4F43, 0x4F44, 0x4F45, 0x4F46, 0x4F47, 0x4F48, 0x4F49, 0x4F4A, 0x4F4B, 0x4F4C, 0x4F4D, 0x4F4E, 0x4F4F, 0x4F50, 0x4F51, 0x4F52, 0x4F53},
  {0x5041, 0x5042, 0x5043, 0x5044, 0x5045, 0x5046, 0x5047, 0x5048, 0x5049, 0x504A, 0x504B, 0x504C, 0x504D, 0x504E, 0x504F, 0x5050, 0x5051, 0x5052, 0x5053},
  {0x5141, 0x5142, 0x5143, 0x5144, 0x5145, 0x5146, 0x5147, 0x5148, 0x5149, 0x514A, 0x514B, 0x514C, 0x514D, 0x514E, 0x514F, 0x5150, 0x5151, 0x5152, 0x5153},
  {0x5241, 0x5242, 0x5243, 0x5244, 0x5245, 0x5246, 0x5247, 0x5248, 0x5249, 0x524A, 0x524B, 0x524C, 0x524D, 0x524E, 0x524F, 0x5250, 0x5251, 0x5252, 0x5253},
  {0x5341, 0x5342, 0x5343, 0x5344, 0x5345, 0x5346, 0x5347, 0x5348, 0x5349, 0x534A, 0x534B, 0x534C, 0x534D, 0x534E, 0x534F, 0x5350, 0x5351, 0x5352, 0x5353},
};

const byte ROWS = 9; //four rows
// THE ROW NEED TO BE ON THE SIDE OF DIODE. MAKE SURE THE COLUMN PINS ARE THE SIDE OF THE MATRIX WIRES WITH DIODES
const byte COLS = 9; //four columns

// PLEASE JUST COPY FROM THE ENTIRE MATRIX

//uint16_t hexaKeys[ROWS][COLS] = {
//  {'AA','AB','AC','AD','AE','AF','AG','AH','AJ'},
//  {'BA','BB','BC','BD','BE','BF','BG','BH','BJ'},
//  {'CA','CB','CC','CD','CE','CF','CG','CH','CJ'},
//  {'DA','DB','DC','DD','DE','DF','DG','DH','DJ'},
//  {'EA','EB','EC','ED','EE','EF','EG','EH','EJ'},
//  {'FA','FB','FC','FD','FE','FF','FG','FH','FJ'},
//  {'GA','GB','GC','GD','GE','GF','GG','GH','GJ'},
//  {'HA','HB','HC','HD','HE','HF','HG','HH','HJ'},
//  {'JA','JB','JC','JD','JE','JF','JG','JH','JJ'}
//};

uint16_t hexaKeys[ROWS][COLS] = {
  {'AA','AB','AC','AD','AE','AF','AG','AH','AI'},
  {'BA','BB','BC','BD','BE','BF','BG','BH','BI'},
  {'CA','CB','CC','CD','CE','CF','CG','CH','CI'},
  {'DA','DB','DC','DD','DE','DF','DG','DH','DI'},
  {'EA','EB','EC','ED','EE','EF','EG','EH','EI'},
  {'FA','FB','FC','FD','FE','FF','FG','FH','FI'},
  {'GA','GB','GC','GD','GE','GF','GG','GH','GI'},
  {'HA','HB','HC','HD','HE','HF','HG','HH','HI'},
  {'IA','IB','IC','ID','IE','IF','IG','IH','II'}
};

//uint16_t hexaKeys[ROWS][COLS] = {
//  {'AA','AB','AC','AD','AE','AF','AG','AH'},
//  {'BA','BB','BC','BD','BE','BF','BG','BH'},
//  {'CA','CB','CC','CD','CE','CF','CG','CH'},
//  {'DA','DB','DC','DD','DE','DF','DG','DH'},
//  {'EA','EB','EC','ED','EE','EF','EG','EH'},
//  {'FA','FB','FC','FD','FE','FF','FG','FH'},
//  {'GA','GB','GC','GD','GE','GF','GG','GH'},
//  {'HA','HB','HC','HD','HE','HF','HG','HH'},
//  {'JA','JB','JC','JD','JE','JF','JG','JH'}
//};

uint16_t testArray[ROWS][COLS];
//
//uint16_t hexaKeys[ROWS][COLS];

//for (int i = 0; i < ROWS; i++)
//{
//  int j = 0;
//}

//Serial.print(testArray[2][3]);

//uint16_t hexaKeys[ROWS][COLS] = {
//  {'AA', 'AB', 'AC', 'AD', 'AE', 'AF', 'AG', 'AH'},
//  {'BA', 'BB', 'BC', 'BD', 'BE', 'BF', 'BG', 'BH'},
//  {'CA', 'CB', 'CC', 'CD', 'CE', 'CF', 'CG', 'CH'},
//  {'DA', 'DB', 'DC', 'DD', 'DE', 'DF', 'DG', 'DH'},
//  {'EA', 'EB', 'EC', 'ED', 'EE', 'EF', 'EG', 'EH'},
//  {'FA', 'FB', 'FC', 'FD', 'FE', 'FF', 'FG', 'FH'},
//  {'GA', 'GB', 'GC', 'GD', 'GE', 'GF', 'GG', 'GH'},
//  {'HA', 'HB', 'HC', 'HD', 'HE', 'HF', 'HG', 'HH'}
//};

// THE ROW NEED TO BE ON THE SIDE OF DIODE. MAKE SURE THE COLUMN PINS ARE THE SIDE OF THE MATRIX WIRES WITH DIODES
//byte rowPins[ROWS] = {14,15,16,17,18,19,20,21,22}; //connect to the row pinouts of the keypad the row needs to
//byte colPins[COLS] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; //connect to the column pinouts of the keypad
//byte colPins[COLS] = {2,3,4,5,6,7,8,9,12};
//byte rowPins[ROWS] = {6,7,8,9}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad

byte rowPins[ROWS] = {2, 3, 4, 5, 6,7,8,9,10}; // diode side00
byte colPins[COLS] = {23,25,27,29,31,33,35,37,39};
//initialize an instance of class NewKeypad
BigKeypad customKeypad = BigKeypad( makeIntKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);

//  for (int i = 0; i < ROWS; i++) {
//    for (int j = 0; j < COLS; j++) {
//      hexaKeys[i][j] = gobanLegend3[i][j];
//      //      Serial.print(hexaKeys[i][j]);
//    }
//  }
}

void loop() {
  if (customKeypad.getKeys()) {
    for (uint16_t i = 0; i < LIST_MAX; i++) {
      if (customKeypad.key[i].stateChanged) {
        if (customKeypad.key[i].kstate == PRESSED) {

            Serial.write(char(customKeypad.key[i].kchar >> 8));
            Serial.write(char(customKeypad.key[i].kchar));
//          Serial.print(char(customKeypad.key[i].kchar >> 8));
//          Serial.print(char(customKeypad.key[i].kchar));

          //          Serial.write('\n'); //newline added for readability in serial monitor
        }
      }
    }
  }
}
