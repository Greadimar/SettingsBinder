# Description
Whole library consists of two parts. BindedSettings and LightBinding.    
BindedSettings has following possibilities:
* Qt widgets can be binded to values, marked as properties, that provides their auto update when widget's control triggered. Works in opposite way either.
* Auto loading and saving for properties in constructor and destructor of object inherited from BindedSettings class
Watch example in settingsbinder.pro

LightBinding is static and has following possibilites:
* Most values can be binded to popular widgets. Has two options: From and To. Binding functions with word "from" will update binding value from current widget's values; "to" will update widget's values from binding value.
* Binding can take a mutex reference as argument for cases when binding values could be read from another thread.

It's still lacks some support for widgets (like QTabWidget), and some code might be outdated. 

# TLDR
Use BindedSettings for auto saving and if you want using Q_PROPERTY (for qml also)
Use LightBinding if you want to save by yourself and don't want huge property construction. 

# Using BindedSettings
For using library u need to do following actions:
1. Clone your project
2. Add in you ".pro" file:
	<pre><code>
	include(settingsbinder/settingsbinder.pri)
	</code></pre>
3. include "settingsbinder/bindedsettings.h"
4. For using BindedSettings, you should make your own class (for example Settings) inherited from BindedSettings
5. In your inherited class make a property :
<pre><code>
	class Settings: public BindedSettings
	{
		Q_OBJECT
	public:
		Q_PROPERTY(QString stringForLe READ stringForLe WRITE setStringForLe NOTIFY stringForLeChanged)
		 //getter:
		QString stringForLe() const;
		//setter:
		void setStringForLe(const QString &stringForLe)
	signals:
		void stringForLeChanged(); 
	private:
		//value
		QString m_stringForLe;				
	}
</code></pre>


6. In you gui class bind widget to property
	<pre><code>
		settings->bindWtToProp(ui->leString, "stringForLe");
			//first argument is your widget (QLineEdit for this case, second - Q_PROPERTY name)
	</code></pre>
7. For binding enum class, u should declare it inside you class and use macro Q_ENUM
<pre><code>
class Settings: public BindedSettings
{
	Q_OBJECT
public:
	enum class States{
		state0 = 0,
		state1 = 1,
		state2 = 2
	};
	//It's important to use Q_ENUM and don't forget to run qmake after
	Q_ENUM(States)											
}
</code></pre>
If you want use namespace, than declare it in the same h. file. (Still figuring out why property is not found if it declared in another .h)
<pre><code>
namespace SomeNamespace{
	Q_NAMESPACE
	enum class wowState{
		wow = 0,
		awesome = 1,
		so_cute = 2			
	}
	Q_ENUM_NS(wowState)
	
}
</code></pre>

8. For binding QButtonGroup to your enum class, don't forget to add buttons
<pre><code>
	btngrpStates = new QButtonGroup();							
	btngrpStates->addButton(ui->radioButton, static_cast<int>(Settings::States::state0);           		
	btngrpStates->addButton(ui->radioButton_2, static_cast<int>(Settings::States::state1);          
	btngrpStates->addButton(ui->radioButton_3, static_cast<int>(Settings::States::state2);    			
	settings->bindWtToProp(btngrpStates, "stateForGrpb");			
</code></pre>

9. You can save and load manually using save() and load() from your class

10. If you need bind hex value to QLineEdit, than add extra argument:
<pre><code>
	settings->bindWtToProp(ui->leUintHex, Settings::IntType::hex);
</code></pre>

# Using LightBinding
1. Clone your project
2. Add in you ".pro" file:
	<pre><code>
	include(settingsbinder/settingsbinder.pri)
	</code></pre>
3. include "settingsbinder/lightbinding.h"
4. If you need to bind value and update it to widget type following:
<pre><code>
	LightBinding::bindSbFromVal(this, someintval, ui->sbEditor);
	// this -  QObject* which will be used as context for connections
	// someintval - integer value that will be binded. Make sure it will not get out of scope!
	// ui->sbEditor - QSpinBox that will be binded to our value	
</code></pre>
5. If you need to bind value and update it with the value from widget, use: 
<pre><code>
LightBinding::bindLeToVal(this, someString, ui->leEditor) ;
	// this -  QObject* which will be used as context for connections
	// someString - string value that will be binded. Make sure it will not get out of scope!
	// ui->leEditor - QLineEdit that will be binded to our value
</code></pre>
6. If you want to bind value and read it from another thread, just pass the mutex
<pre><code>
LightBinding::bindChbToVal(this, someBool, m_mutex, ui->chbEditor) ;
	// this -  QObject* which will be used as context for connections
	// someBool - boolean value that will be binded. Make sure it will not get out of scope!
	// m_mutex - your mutex. Make sure it will not get out of scope!
	// ui->chbEditor - QCheckBox that will be binded to our value
</code></pre>

	
