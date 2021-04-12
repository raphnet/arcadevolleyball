CC=sdcc
IHX2SMS=ihx2sms
DEVKITSMS=/root/devkitSMS
VERSION_MAJ=1
VERSION_MIN=2
VERSION_STR=\"$(VERSION_MAJ).$(VERSION_MIN)\"
CFLAGS=-mz80 -I$(DEVKITSMS)/SMSlib/src/ --peep-file $(DEVKITSMS)/SMSlib/src/peep-rules.txt -I$(DEVKITSMS)/PSGlib/src/ -DVERSION_STR=$(VERSION_STR) -DVERSION_MAJ=$(VERSION_MAJ) -DVERSION_MIN=$(VERSION_MIN)
LDFLAGS=--no-std-crt0 --data-loc 0xC000 $(DEVKITSMS)/crt0/crt0_sms.rel $(DEVKITSMS)/PSGlib/PSGlib.rel


OBJS=avb.rel stubs.rel data.rel util.rel

ALL_OBJS=$(OBJS)

ROM=avb.sms

all: $(ROM)

flash:
	../../../smscprog1/client/dumpcart.py -p $(ROM)


main.rel: main.c stubs.h data.h util.h
	$(CC) $(CFLAGS) -c $<

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

%.rel: %.c %.h
	$(CC) $(CFLAGS) -c $<

avb.ihx:	$(ALL_OBJS)
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $^ -lSMSlib

$(ROM): avb.ihx
	$(IHX2SMS) $< $@

clean:
	rm $(OBJS) *.ihx *.sms

run:
	./m.sh
	/usr/src/raph/meka/meka/meka $(ROM)

run_emulicious:
	java -jar /usr/src/raph/emulicious/Emulicious.jar ./$(ROM)
