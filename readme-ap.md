
IAS
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
00  | ZOOM   | big   | small |       |        | enter  |
01  | direct | menu  | fpl   | ent   | proc   | clr    |

DEFUAL MODE G1000N1
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
10n1|        | INSET |       | PFD   |        | CDI    |
11n1| DME    | XPDR  | IDENT | TMR   | NRST   | ALERTS |

DEFUAL MODE G1000N2
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
10n2| SYSTEM |       | MAP   |       |        |        |
11n2|        |       |       | DCLTR |        |        |


g1000 n1 mode INSERT
mode| ap     | HDG   | NAV   | IAS    | ALT    | VS      |
10n1| OFF    | DCLTR |       | TRAFIC | TOPO   | TARRAIN |
11n1|        |       |       |        | BACK   |         |

g1000 n1 mode PFD
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
10n1|        | DFLTS | WIND  | DME   | BRG1   |        |
11n1| BRG2   |       | BARO  | STD   | BACK   |        |

g1000 n1 mode BARO 
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
10n1|        |       |       |       |        |        |
11n1|        | IN    | HPA   |       | BACK   |        |

g1000 n1 mode XPDR
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
10n1|        |       | STBY  | ON    | ALT    |        |
11n1| VFR    | CODE  | IDENT |       | BACK   |        |

g1000 n1 mode CODE XPDR
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
10n1| 0      | 1     | 2     | 3     | 4      | 5      |
11n1| 6      | 7     | IDENT | BKSP| BACK   |        |

g1000 n2 mode SYSTEM
mode| ap     | HDG   | NAV   | IAS   | ALT    | VS     |
10n2| SYSTEM |       |       | DEC   | INC    | RESET  |
11n2|        |       |       |       |        |        |

g1000 n2 mode TRAFIC
mode| ap     | HDG   | NAV   | IAS     | ALT     | VS     |
10n2| TRAFIC |       | TORO  | TERRAIN | AIRWAYS |        |
11n2| NEXRAD |       |       |         |         |        |
