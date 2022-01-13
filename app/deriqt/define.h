#pragma once


// #define LOG(format, ...) printf(format, __VA_ARGS__)

//Trader Handler Task 
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONRSPAUTHENTICATE 3
#define ONRSPUSERLOGIN 4
#define ONRSPUSERLOGOUT 5
#define ONRSPUSERPASSWORDUPDATE 6
#define ONRSPTRADINGACCOUNTPASSWORDUPDATE 7
#define ONRSPUSERAUTHMETHOD 8
#define ONRSPGENUSERCAPTCHA 9
#define ONRSPGENUSERTEXT 10
#define ONRSPORDERINSERT 11
#define ONRSPPARKEDORDERINSERT 12 //预埋单报单请求响应
#define ONRSPPARKEDORDERACTION 13 //预埋撤单请求响应
#define ONRSPORDERACTION 14
#define ONRSPQUERYMAXORDERVOLUME 15
#define ONRSPSETTLEMENTINFOCONFIRM 16
#define ONRSPREMOVEPARKEDORDER 17
#define ONRSPREMOVEPARKEDORDERACTION 18
#define ONRSPEXECORDERINSERT 19
#define ONRSPEXECORDERACTION 20
#define ONRSPFORQUOTEINSERT 21
#define ONRSPQUOTEINSERT 22
#define ONRSPQUOTEACTION 23
#define ONRSPBATCHORDERACTION 24
#define ONRSPOPTIONSELFCLOSEINSERT 25
#define ONRSPOPTIONSELFCLOSEACTION 26
#define ONRSPCOMBACTIONINSERT 27
#define ONRSPQRYORDER 28
#define ONRSPQRYTRADE 29
#define ONRSPQRYINVESTORPOSITION 30
#define ONRSPQRYTRADINGACCOUNT 31
#define ONRSPQRYINVESTOR 32
#define ONRSPQRYTRADINGCODE 33
#define ONRSPQRYINSTRUMENTMARGINRATE 34
#define ONRSPQRYINSTRUMENTCOMMISSIONRATE 35
#define ONRSPQRYEXCHANGE 36
#define ONRSPQRYPRODUCT 37
#define ONRSPQRYINSTRUMENT 38
#define ONRSPQRYDEPTHMARKETDATA 39
#define ONRSPQRYSETTLEMENTINFO 40
#define ONRSPQRYTRANSFERBANK 41
#define ONRSPQRYINVESTORPOSITIONDETAIL 42
#define ONRSPQRYNOTICE 43
#define ONRSPQRYSETTLEMENTINFOCONFIRM 44
#define ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL 45
#define ONRSPQRYCFMMCTRADINGACCOUNTKEY 46
#define ONRSPQRYEWARRANTOFFSET 47
#define ONRSPQRYINVESTORPRODUCTGROUPMARGIN 48
#define ONRSPQRYEXCHANGEMARGINRATE 49
#define ONRSPQRYEXCHANGEMARGINRATEADJUST 50
#define ONRSPQRYEXCHANGERATE 51
#define ONRSPQRYSECAGENTACIDMAP 52
#define ONRSPQRYPRODUCTEXCHRATE 53
#define ONRSPQRYPRODUCTGROUP 54
#define ONRSPQRYMMINSTRUMENTCOMMISSIONRATE 55
#define ONRSPQRYMMOPTIONINSTRCOMMRATE 56
#define ONRSPQRYINSTRUMENTORDERCOMMRATE 57
#define ONRSPQRYSECAGENTTRADINGACCOUNT 58
#define ONRSPQRYSECAGENTCHECKMODE 59
#define ONRSPQRYSECAGENTTRADEINFO 60
#define ONRSPQRYOPTIONINSTRTRADECOST 61
#define ONRSPQRYOPTIONINSTRCOMMRATE 62
#define ONRSPQRYEXECORDER 63
#define ONRSPQRYFORQUOTE 64
#define ONRSPQRYQUOTE 65
#define ONRSPQRYOPTIONSELFCLOSE 66
#define ONRSPQRYINVESTUNIT 67
#define ONRSPQRYCOMBINSTRUMENTGUARD 68
#define ONRSPQRYCOMBACTION 69
#define ONRSPQRYTRANSFERSERIAL 70
#define ONRSPQRYACCOUNTREGISTER 71
#define ONRSPERROR 72
#define ONRTNORDER 73
#define ONRTNTRADE 74
#define ONERRRTNORDERINSERT 75
#define ONERRRTNORDERACTION 76
#define ONRTNINSTRUMENTSTATUS 77
#define ONRTNBULLETIN 78
#define ONRTNTRADINGNOTICE 79
#define ONRTNERRORCONDITIONALORDER 80
#define ONRTNEXECORDER 81
#define ONERRRTNEXECORDERINSERT 82
#define ONERRRTNEXECORDERACTION 83
#define ONERRRTNFORQUOTEINSERT 84
#define ONRTNQUOTE 85
#define ONERRRTNQUOTEINSERT 86
#define ONERRRTNQUOTEACTION 87
#define ONRTNFORQUOTERSP 88
#define ONRTNCFMMCTRADINGACCOUNTTOKEN 89
#define ONERRRTNBATCHORDERACTION 90
#define ONRTNOPTIONSELFCLOSE 91
#define ONERRRTNOPTIONSELFCLOSEINSERT 92
#define ONERRRTNOPTIONSELFCLOSEACTION 93
#define ONRTNCOMBACTION 94
#define ONERRRTNCOMBACTIONINSERT 95
#define ONRSPQRYCONTRACTBANK 96
#define ONRSPQRYPARKEDORDER 97
#define ONRSPQRYPARKEDORDERACTION 98
#define ONRSPQRYTRADINGNOTICE 99
#define ONRSPQRYBROKERTRADINGPARAMS 100
#define ONRSPQRYBROKERTRADINGALGOS 101
#define ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN 102
#define ONRTNFROMBANKTOFUTUREBYBANK 103
#define ONRTNFROMFUTURETOBANKBYBANK 104
#define ONRTNREPEALFROMBANKTOFUTUREBYBANK 105
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 106
#define ONRTNFROMBANKTOFUTUREBYFUTURE 107
#define ONRTNFROMFUTURETOBANKBYFUTURE 108
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL 109
#define ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL 110
#define ONRTNQUERYBANKBALANCEBYFUTURE 111
#define ONERRRTNBANKTOFUTUREBYFUTURE 112
#define ONERRRTNFUTURETOBANKBYFUTURE 113
#define ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL 114
#define ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL 115
#define ONERRRTNQUERYBANKBALANCEBYFUTURE 116
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTURE 117
#define ONRTNREPEALFROMFUTURETOBANKBYFUTURE 118
#define ONRSPFROMBANKTOFUTUREBYFUTURE 119
#define ONRSPFROMFUTURETOBANKBYFUTURE 120
#define ONRSPQUERYBANKACCOUNTMONEYBYFUTURE 121
#define ONRTNOPENACCOUNTBYBANK 122
#define ONRTNCANCELACCOUNTBYBANK 123
#define ONRTNCHANGEACCOUNTBYBANK 124

// Market Handler task, FXXX for future, OXXX for options. 
#define FDEPTHMKT 125
#define INSTRUMENTNUM 126
#define KLINENUM 127

//Strategyy Handler 
#define LONGOPEN 128
#define SHORTOPEN 129
#define LONGCLOSE 130
#define SHORTCLOSE 131

//Strategy Name
#define BASESTRATEGY 132
#define DATASTRATEGY 133
#define TSTRATEGY 134

//datatype
#define ORDERFIELDCTP 135
#define ORDERFIELDSIM 136


//gmsimtrade status
#define ONSIMCONNECTED 137
#define ONSIMDISCONNECTED 138
#define ONSIMORDERSTATUS 139
#define ONSIMEXECUTIONREPORT 141


//signal 
#define LONG_SIGNAL 142
#define SHORT_SIGNAL 143
#define NO_SIGNAL 144
