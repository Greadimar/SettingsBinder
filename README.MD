#SettingsBinder
Библиотека имеет следующие возможности:
* готовые qt виджеты можно привязать к заданным переменным, что обеспечивает их автоматическое изменение при управлении виджетом и наоборот
* автоматическое сохранение заданных переменных 
* автоматическая загрузка заданных  переменных в программу и привязанные виджеты

Для наглядного представления можно клонировать проект и подключить settingsbinder.pro

#Использование
Для использования возможностей библиотеки требуется выполнить следующие действия:
1. Склонировать проект в папку
2. Добавить в .pro файл своего проекта, например:
	<pre><code>
	include($$(SHARED_LIBS)/settingsbinder/settingsbinder.pri)
	</code></pre>
(если директория SHARED_LIBS записана в системных переменных, иначе просто выбрать путь)
3. Для записи переменных создать класс, унаследованный от BindedSettings
4. В унаследованном классе создать переменные следующим образом:
	<pre><code>
	class Settings: public BindedSettings
	{
		Q_OBJECT
	public:
		Q_PROPERTY(QString stringForLe READ stringForLe WRITE setStringForLe NOTIFY stringForLeChanged)
		QString stringForLe() const;							//функция getter (возвращающая m_stringForLe)
		void setStringForLe(const QString &stringForLe);		//функция setter (устанавливает m_stringForLe)
	private:
		QString m_stringForLe;									//переменная
	</code></pre>
Данное действие удобно выполнить в среде QtCreator, создав переменную m_stringForLe, затем нажать правой кнопкой мыши на ней и выбрать "рефакторинг - установить методы получения и установки значения"
5. В классе интерфейса привязать виджет к переменной
	<pre><code>
		settings->bindWtToProp(ui->leString, "stringForLe");	//первый аргумент - виджет, второй - значение из Q_PROPERTY
	</code></pre>
6. Для привязки enum class к поддерживаемому виджету требуется в унаследованном от BindedSettings классе написать следующее:
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
		Q_ENUM(States)											//Обязательно регистрируем наш класс в Q_ENUM
		Q_PROPERTY(States stateForGrpb READ stateForGrpb WRITE setStateForGrpb NOTIFY stateForGrpbChanged)
		Settings::States stateForGrpb() const;					//функция getter (возвращающая m_stringForLe)
		void setStateForGrpb(const States &stateForGrpb);		//функция setter (устанавливает m_stringForLe)
		Q_INVOKABLE QVariant stateForGrpbVariant(int val){		//обязательная функция для преобразования в QVariant
			return getVariantEnumClass<States>(val);
		}
	private:
		State m_state;									//переменная
	</code></pre>

7. В классе интерфейса привязать QButtonGroup к переменной enum class
	<pre><code>
		btngrpStates = new QButtonGroup();									// создаём пустую группу кнопок
		btngrpStates->addButton(ui->radioButton, static_cast<int>(Settings::States::state0);            			// добавляем кнопки, соответствующие значению enum class в int
		btngrpStates->addButton(ui->radioButton_2, static_cast<int>(Settings::States::state1));          
		btngrpStates->addButton(ui->radioButton_3, static_cast<int>(Settings::States::state2);          
		settings->bindButtonGroupAsEnum<Settings::States>(btngrpStates, "stateForGrpb");							//первый аргумент - виджет, второй - значение из Q_PROPERTY
	</code></pre>

8. Сохранение и загрузку данных осуществлять через save() и load() унаследованного от BindedSettings класса

# Особые случаи
1. Если требуется QLineEdit привязать данные формата HEX, то нужно в классе интерфейса добавить следующую строку перед привязкой:
	<pre><code>
	    settings->setIntTypePropertyTo(ui->leUintHex, Settings::IntType::hex);
	</code></pre>
2. Если требуется сохранять и загружать переменные для класса, не унаследованного от BindedSettings, но унаследованного от QObject, то следует задать в нём переменные по тому же принципу(см п.4 пред. абзаца) и для сохранения и загрузки использовать объект класса SettingsSaver:
	<pre><code>
	    SettingsSaver* settingsSaver = new SettingsSaver(myObjectWithProperties);
		settingsSaver.load();
		settingsSaver.save();
	</code></pre>

# Поддерживаемые привязки на текущий момент:
	QLineEdit - QString / uint (decimal) / uint (hex) / int / short / long / double 
	QComboBox - int
	QSpinBox - int
	QDoubleSpinBox - double
	QCheckBox - bool
	QGroupButton - enum class
	