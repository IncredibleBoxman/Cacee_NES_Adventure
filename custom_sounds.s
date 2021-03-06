;this file for FamiTone2 libary generated by FamiStudio
      .export _custom_sounds
_custom_sounds:
	.word @ntsc
	.word @ntsc
@ntsc:
	.word @sfx_ntsc_1up
	.word @sfx_ntsc_break
	.word @sfx_ntsc_bump
	.word @sfx_ntsc_coin1
	.word @sfx_ntsc_coin2
	.word @sfx_ntsc_death
	.word @sfx_ntsc_explosion
	.word @sfx_ntsc_jump1
	.word @sfx_ntsc_jump2
	.word @sfx_ntsc_land
	.word @sfx_ntsc_menubeep1
	.word @sfx_ntsc_menubeep2
	.word @sfx_ntsc_pause
	.word @sfx_ntsc_playerhurt
	.word @sfx_ntsc_powerup
	.word @sfx_ntsc_start
	.word @sfx_ntsc_stompenemy
	.word @sfx_ntsc_throwstuff

@sfx_ntsc_1up:
	.byte $82,$00,$81,$70,$80,$bf,$89,$f0,$03,$85,$00,$84,$70,$83,$b6,$02
	.byte $80,$b0,$01,$81,$64,$80,$bf,$02,$83,$b0,$01,$84,$64,$83,$b6,$02
	.byte $80,$b0,$01,$81,$59,$80,$bf,$02,$83,$b0,$01,$84,$59,$83,$b6,$02
	.byte $80,$b0,$01,$81,$38,$80,$bf,$02,$83,$b0,$01,$84,$38,$83,$b6,$02
	.byte $80,$b0,$03,$83,$b0,$04,$80,$b3,$03,$83,$b2,$02,$80,$b0,$03,$83
	.byte $b0,$04,$80,$b1,$03,$83,$b1,$02,$80,$b0,$03,$00
@sfx_ntsc_break:
	.byte $82,$00,$81,$8e,$80,$78,$85,$01,$84,$2d,$83,$b8,$89,$f0,$01,$84
	.byte $1b,$01,$84,$09,$01,$85,$00,$84,$f7,$01,$84,$e5,$01,$80,$70,$84
	.byte $d5,$01,$81,$7e,$80,$78,$85,$01,$84,$0a,$01,$85,$00,$84,$f9,$01
	.byte $84,$e7,$01,$84,$d6,$01,$84,$c4,$01,$80,$70,$84,$b3,$01,$81,$70
	.byte $80,$78,$84,$eb,$01,$84,$da,$01,$84,$c8,$01,$84,$b7,$01,$84,$a5
	.byte $01,$80,$70,$84,$96,$01,$81,$64,$80,$78,$84,$cf,$01,$84,$bd,$01
	.byte $84,$ab,$01,$84,$99,$01,$84,$87,$01,$80,$70,$84,$77,$01,$80,$72
	.byte $83,$b0,$05,$80,$70,$01,$80,$71,$03,$00
@sfx_ntsc_bump:
	.byte $82,$00,$81,$70,$80,$b8,$89,$f0,$03,$81,$4b,$85,$00,$84,$70,$83
	.byte $33,$03,$84,$4b,$1b,$80,$b0,$00
@sfx_ntsc_coin1:
	.byte $82,$00,$81,$54,$80,$b8,$89,$f0,$03,$81,$38,$85,$00,$84,$54,$83
	.byte $33,$03,$84,$38,$1b,$80,$b0,$00
@sfx_ntsc_coin2:
	.byte $85,$02,$84,$13,$83,$ba,$89,$f0,$01,$84,$2c,$01,$84,$44,$01,$84
	.byte $5c,$01,$00
@sfx_ntsc_death:
	.byte $85,$01,$84,$55,$83,$bf,$89,$f0,$01,$84,$43,$01,$84,$31,$01,$84
	.byte $1f,$01,$84,$0d,$01,$85,$00,$84,$fd,$01,$00
@sfx_ntsc_explosion:
	.byte $85,$01,$84,$40,$83,$bf,$89,$f0,$01,$84,$2e,$01,$84,$1c,$01,$84
	.byte $0a,$01,$85,$00,$84,$f8,$01,$84,$e6,$01,$84,$d4,$01,$84,$c2,$01
	.byte $84,$b0,$01,$84,$9f,$01,$00
@sfx_ntsc_jump1:
	.byte $8a,$0b,$89,$3a,$04,$00
@sfx_ntsc_jump2:
	.byte $85,$00,$84,$c5,$83,$7f,$89,$f0,$01,$85,$01,$84,$05,$01,$84,$44
	.byte $01,$84,$84,$01,$84,$c3,$01,$85,$02,$84,$03,$01,$00
@sfx_ntsc_land:
	.byte $82,$02,$81,$1a,$80,$7f,$8a,$0a,$89,$38,$01,$82,$01,$81,$0c,$01
	.byte $82,$02,$81,$1a,$85,$02,$84,$1a,$83,$72,$01,$80,$70,$01,$81,$3a
	.byte $80,$7f,$01,$82,$01,$81,$1c,$83,$70,$01,$82,$02,$81,$3a,$84,$3a
	.byte $83,$72,$01,$80,$70,$01,$81,$5c,$80,$7f,$01,$82,$01,$81,$2d,$83
	.byte $70,$01,$82,$02,$81,$5c,$84,$5c,$83,$72,$01,$80,$70,$01,$81,$80
	.byte $80,$7f,$01,$82,$01,$81,$3f,$83,$70,$01,$82,$02,$81,$80,$84,$80
	.byte $83,$72,$01,$80,$70,$01,$81,$a6,$80,$7f,$01,$82,$01,$81,$52,$83
	.byte $70,$01,$82,$02,$81,$a6,$84,$a6,$83,$72,$01,$80,$70,$02,$83,$70
	.byte $01,$00
@sfx_ntsc_menubeep1:
	.byte $85,$01,$84,$eb,$83,$b6,$89,$f0,$01,$84,$db,$01,$84,$cb,$01,$84
	.byte $bb,$01,$84,$ab,$01,$83,$b0,$01,$84,$3f,$83,$b6,$01,$84,$2c,$01
	.byte $84,$19,$01,$84,$06,$01,$85,$00,$84,$f3,$01,$84,$e1,$01,$00
@sfx_ntsc_menubeep2:
	.byte $85,$00,$84,$60,$83,$bf,$8a,$80,$89,$3f,$01,$84,$62,$01,$84,$64
	.byte $01,$84,$66,$01,$84,$68,$01,$84,$6a,$01,$84,$6c,$01,$84,$6e,$01
	.byte $84,$70,$01,$84,$72,$01,$84,$74,$01,$84,$76,$01,$84,$78,$01,$84
	.byte $7a,$01,$84,$7c,$01,$84,$7e,$03,$83,$b0,$00
@sfx_ntsc_pause:
	.byte $8a,$06,$89,$3f,$01,$8a,$05,$89,$36,$01,$8a,$04,$89,$3f,$01,$8a
	.byte $03,$89,$36,$01,$8a,$02,$89,$3f,$01,$8a,$01,$89,$36,$01,$8a,$00
	.byte $89,$3f,$01,$8a,$0e,$89,$36,$01,$8a,$0c,$89,$3f,$01,$8a,$0a,$89
	.byte $36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f
	.byte $01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01
	.byte $89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89
	.byte $36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$00
@sfx_ntsc_playerhurt:
	.byte $8a,$02,$89,$3f,$01,$8a,$01,$89,$36,$01,$8a,$00,$89,$3f,$01,$8a
	.byte $0f,$89,$36,$01,$8a,$0e,$89,$3f,$01,$8a,$0d,$89,$36,$01,$8a,$0c
	.byte $89,$3f,$01,$8a,$0a,$89,$36,$01,$8a,$08,$89,$3f,$01,$8a,$06,$89
	.byte $36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f
	.byte $01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01
	.byte $89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89
	.byte $36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f
	.byte $01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01
	.byte $89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89
	.byte $36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f
	.byte $01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01
	.byte $89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89,$36,$01,$89,$3f,$01,$89
	.byte $36,$01,$89,$3f,$01,$89,$36,$01,$00
@sfx_ntsc_powerup:
	.byte $82,$00,$81,$54,$80,$3f,$89,$f0,$03,$85,$00,$84,$54,$83,$38,$03
	.byte $81,$7e,$03,$84,$7e,$03,$81,$5e,$03,$84,$5e,$03,$81,$46,$03,$84
	.byte $46,$03,$80,$30,$83,$30,$06,$80,$38,$06,$80,$30,$06,$80,$33,$06
	.byte $00
@sfx_ntsc_start:
	.byte $82,$00,$81,$5e,$80,$bf,$89,$f0,$02,$85,$00,$84,$5e,$83,$b6,$02
	.byte $81,$8e,$02,$84,$8e,$02,$80,$b0,$02,$00
@sfx_ntsc_stompenemy:
	.byte $82,$00,$81,$c2,$80,$b5,$89,$f0,$01,$81,$96,$01,$80,$b0,$85,$00
	.byte $84,$c2,$83,$b1,$01,$84,$96,$01,$00
@sfx_ntsc_throwstuff:
	.byte $82,$01,$81,$01,$80,$b5,$89,$f0,$01,$82,$00,$81,$d5,$01,$80,$b0
	.byte $85,$01,$84,$01,$83,$b1,$01,$85,$00,$84,$d5,$01,$00


