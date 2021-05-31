(*!------------------------------------------------------------
 * [[APP_NAME]] ([[APP_URL]])
 *
 * @link      [[APP_REPOSITORY_URL]]
 * @copyright Copyright (c) [[COPYRIGHT_YEAR]] [[COPYRIGHT_HOLDER]]
 * @license   [[LICENSE_URL]] ([[LICENSE]])
 *------------------------------------------------------------- *)

{---put your main dependencies registration here---}

{$IFDEF USE_SYNAPSE}
        container.add(
            'mailer',
            TSynapseMailerFactory.create()
                .host(config.getString('mailer.host'))
                .port(config.getInt('mailer.port'))
                .username(config.getString('mailer.username'))
                .password(config.getString('mailer.password'))
                .useTls(config.getBool('mailer.useTLS'))
                .useSsl(config.getBool('mailer.useSSL'))
        );
{$ELSE}
    {$IFDEF USE_INDY}
        container.add(
            'mailer',
            TIndyMailerFactory.create()
                .host(config.getString('mailer.host'))
                .port(config.getInt('mailer.port'))
                .username(config.getString('mailer.username'))
                .password(config.getString('mailer.password'))
                .useTls(config.getBool('mailer.useTLS'))
                .useSsl(config.getBool('mailer.useSSL'))
        );
    {$ELSE}
        container.add('mailer', TSendmailMailerFactory.create());
    {$ENDIF}

{$ENDIF}


container.add(
    'logger',
    TBackgroundThreadLoggerFactory.create(
        TMailLoggerFactory
            .create()
            .mailer('mailer')
            .recipient(config.getString('logger.mailer.recipient'))
    )
);