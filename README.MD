# Описание
Библиотека состоит из двух частей. BindedSettings and LightBinding.    
BindedSettings имеет следующие возможности:
* Qt widgets могут быть привязаны к значениям, помеченным как Q_PROPERTY, что обеспечивает их автоматическое обновление при изменении виджета. Может быть реализовано и обратное через сигнал, отмеченные в макросе Q_PROPERTY
* Авто сохранение и загрузка в деструкторе и конструкторе соответственно всех значений помеченных как Q_PROPERTY у классов, унаследованных от BindedSettings
Пример settingsbinder.pro

LightBinding - набор статических функций со следующими возможностям:
* Большинство значений могут быть привязаны к популярным значений. Есть две опции: From и To. Привязка через функции со словом "from" привяжет значение к виджету, считав из него текущее значение. "To" привяжет значение с виджетом, записав текущее значение в него.
* Привязка также может принимать ссылку на QMutex для синхронизации значений с другими потоками.

SbVariantSaver - функции для загрузки и сохранения значений, указанныех в Q_PROPERTIES для конкретного QObject, 
а также сохранение и загрузки пользовательского вектора QVariants.

SbAutoSaver - автоматическое сохранение и загрузка POD структур.

# TLDR
Используйте BindedSettings для автосохранения объектов, содержащих Q_PROPERTY (для qml, например)
Используйте LightBinding если хотите привязывать значения к виджетам, а сохранять другими средствами.
Используйте SbAutoSaver если нужно сохранить или загрузить простую структуру целиком.
Используйте SbVariantSaver для работы с QVariant.

# Использование BindedSettings
Для использования делаем следующее:
1. Клонируем проект
2. Добавляем в ".pro" файл:
	<pre><code>
	include(settingsbinder/settingsbinder.pri)
	</code></pre>
3. #include "settingsbinder/bindedsettings.h" в нужном классе
4. Для использования BindedSettings, нужно сделать свой класс (смотри пример Settings) унаследованный от BindedSettings
5. В наследнике создадим property :
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


6. В классе интерфейса привяжем виджет к property
	<pre><code>
		settings->bindWtToProp(ui->leString, "stringForLe");
			//first argument is your widget (QLineEdit for this case, second - Q_PROPERTY name)
	</code></pre>
7. Для привязывания enum class,нужно определить его внутри Вашего класса и использовать макрос Q_ENUM
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
Если через Namespace, трогда важно объявить его в том же h. файле.
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

8. для привязки QButtonGroup к enum class, не забываем добавлять кнопки
<pre><code>
	btngrpStates = new QButtonGroup();							
	btngrpStates->addButton(ui->radioButton, static_cast<int>(Settings::States::state0);           		
	btngrpStates->addButton(ui->radioButton_2, static_cast<int>(Settings::States::state1);          
	btngrpStates->addButton(ui->radioButton_3, static_cast<int>(Settings::States::state2);    			
	settings->bindWtToProp(btngrpStates, "stateForGrpb");			
</code></pre>

9. Можно сохранять и загружать через save() load() из вашего класса

10. Если требуется привязать Hex значение к QLineEdit, нужно добавить следующие аргумент:
<pre><code>
	settings->bindWtToProp(ui->leUintHex, Settings::IntType::hex);
</code></pre>

# Использование LightBinding
1. Клонируем проект
2. Жобавляем ".pro" file:
	<pre><code>
	include(settingsbinder/settingsbinder.pri)
	</code></pre>
3. Подключаем "settingsbinder/lightbinding.h"
4. Если требуется привязать данные и обновить их в виджет:
<pre><code>
        LightBinding::bindSbFromVal(someintval, ui->sbEditor);
	// someintval - integer value that will be binded. Make sure it will not get out of scope!
	// ui->sbEditor - QSpinBox that will be binded to our value	
</code></pre>
5. Если требуется привязать данные и обновить их из виджета: 
<pre><code>
LightBinding::bindLeToVal(someString, ui->leEditor) ;
	// someString - string value that will be binded. Make sure it will not get out of scope!
	// ui->leEditor - QLineEdit that will be binded to our value
</code></pre>
6. Если надо привязать и читать из другого потока, то просто предоставьте мьютекс
<pre><code>
LightBinding::bindChbToVal(someBool, m_mutex, ui->chbEditor) ;
	// someBool - boolean value that will be binded. Make sure it will not get out of scope!
	// m_mutex - your mutex. Make sure it will not get out of scope!
	// ui->chbEditor - QCheckBox that will be binded to our value
</code></pre>

	
