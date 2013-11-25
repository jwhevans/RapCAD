/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2013 Giles Bathgate
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QApplication>
#else
#include <QtGui/QApplication>
#include <QTextCodec>
#define SETCODEC
#endif

#include <QTextStream>
#include "mainwindow.h"
#include "worker.h"
#include "getopt.h"
#include "preferences.h"
#include "tester.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
static int version()
{
	QTextStream output(stdout);
	output << "RapCAD version: " << TOSTRING(RAPCAD_VERSION) << "\n";
	output.flush();
	return 0;
}

static int showUi(QApplication& a,QString filename)
{
	QCoreApplication::setOrganizationName("rapcad");
	QCoreApplication::setOrganizationDomain("rapcad.org");
	QCoreApplication::setApplicationName("RapCAD");
	QCoreApplication::setApplicationVersion(TOSTRING(RAPCAD_VERSION));

	MainWindow w;

	if(!filename.isEmpty())
		w.loadFile(filename);

	w.show();

	int retcode=a.exec();
	Preferences::syncDelete();
	return retcode;
}

int commandLine(QCoreApplication& a, Worker* b, QString inputFile, QString outputFile,bool print)
{
	b->setup(inputFile,outputFile,print,false);
	b->evaluate();
	a.quit();
	return 0;
}


int main(int argc, char* argv[])
{
	int opt;
	QString outputFile;
	QString inputFile;
	bool print=false;
	bool useGUI=true;

#ifdef SETCODEC
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

	QTextStream output(stdout);
	Worker* w;

	while((opt = getopt(argc, argv, "o:pvt")) != -1) {
		switch(opt) {
		case 'v':
			return version();
		case 't':
			useGUI=false;
			w=new Tester(output);
			break;
		case 'p':
			print=true;
		case 'o':
			useGUI=false;
			outputFile=QString(optarg);
			w=new Worker(output);
		}
	}

	inputFile=QString(argv[optind]);

	if(!useGUI) {
		QCoreApplication a(argc,argv);
		return commandLine(a,w,inputFile,outputFile,print);
	} else {
		QApplication a(argc,argv);
		return showUi(a,inputFile);
	}
}
