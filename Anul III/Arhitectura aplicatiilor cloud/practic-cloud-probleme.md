## System Design CAA - Solutii

#### 1. Your orgznization is running on a business-critical learning management system (LMS) on its own infrastructure on-premises. Since the platform has been growing exponentially, the stakeholders decided to migrate it to AWS. You are part of the development team and you are responsible for choosing the right services and designing the solution.
__The system enables teachers and experts to market, sell, and present their courses to people willing to learn from all around the world. Each course might contain written documents (mostly PDFs and PowerPoint presentations), videos, and images/diagrams. Other functional requirements include:__
- __students can be notified via email__
- __each course goes through a review process before being published__
- __teachers have access to the API of the system enabling them to publish the courses on their own websites__

<br>__The LMS is composed of several backend modules written in Java and Node.js, which store data in MySQL databases, while the frontend is built with React. Your team has been struggling lately to run the system locally due to its distributed nature and the increasing number of dependencies. Another important consideration is that the system transcodes the videos before the course is published in order to optimize bandwidth and playback.__
<br>__Since this is the core product of your organization, the main focus of the design must be the availability of the system and reducing operational/maintenance overhead. Of course, the cost must be optimized whenever possible.__
<br><br>_Describe your solution below. Mention which AWS services you would choose, how they communicate with each other, and, equally important, why you have chosen a particular service. Be as explicit as possible._
<br>_Optionally, you can upload images to illustrate your design (feel free to use any drawing or diagram tool you wish; images don't have to be pretty)._
<br><br>

> We would like to propose the following solution:
> * __EC2__, for hosting the React frontend, to allow for the scale of resources based on demand. Costs could also be reduced by using reserved instances.
> * __S3__, to store the course provided documents (PDFs, PPTs, videos, images). It is standard practice to use S3 for object storage, for its infinite space, and the cost-effective and secure operation. We can also leverage other features such as lifecycle policies and server-side encryption, and we can use different S3 Buckets for our various object types.
> * __CloudFront__, AWS's CDN to serve content to the users from all around the world, depending on their location. CloudFront is fast, has a global network and edge locations and is preferred for cases when people from all around the world need to be able to access the system. It has improved global latency, DDoS protection and easy integration with S3.
> * __Lambda__, to transcode the uploaded course. Lambda is serverless and on-demand and, therefore, we do not need to manage servers when there isn't demand for our transcoding functionality. Costs are determined based on the duration of its execution and the quantity of resources used, therefore minimal. Scalability is available, since Lambda scales automatically based on the number of incoming requests.
> * __SQS (Simple Queue Service) Queues__ and __SNS (Simple Notification Service) Topics__, to send emails to students. They are reliable, cost-effective notification systems and do not require additional infrastructure. They can work together in an event-driven architecture by allowing applications to publish events to topics, while queues subscribe to these topics. It is a decoupled, distributed and asynchronous message delivery system.
> * __API Gateway__, for enabling teachers to make use of the API endpoints. It is a fully-managed service, easily-maintainable, making it easy for developers to handle APIs at any scale. It also provides important security features like authentication and authorization for our sensitive data. Pricing is calculated based solely on the API calls received and the amount of data transfered, therefore it is a cost-effective solution.
> * __RDS (Relational Database Service)__, to manage MySQL database instances with less maintenance. RDS proides automated backups, maintenance and scaling options, lifting the routine database administration responsibilites from the developers.
> * __Application Load Balancer__, to make the platform more efficient and provide a safety net in case of instance failure or downtime, redirecting traffic to available ones so that the service can remain available and not affect user experience.
> * __Cognito__, to manage users and their access. We can leverage Cognito user pool groups and roles to handle the different types of users/roles (students, teachers, experts) and the authorization of API calls on the Gateway based on their group. Cognito is reliable, scalable and can be configured with social logins, a convenient solution. It also provides multi-factor authentication.
> * A __VPC (Virtual Private Cloud)__ is needed, to configure and launch the AWS resources, preferrably with two defined subnets: a public one to be used for resources that connect to the internet, like the backend, and a private one for resources solely accessed through the application tier (inside the VPC). We can also leverage Access Control Lists and security groups.
> * __ECS (Elastic Container Service)__, to dockerize and launch the containers for the backend, for ease of testing, running and deployment on part of the development team.
> * __IAM (Identity and Access Management) Roles__, to secure data at rest and in transit with the principle of least privilege for the EC2 instances, Lambda functions and other resources.

> In the future, the afore-mentioned solutions can be adjusted/tuned for cost and speed efficiency, should the platform grow for more traffic. We could improve it further with auto-scaling configurations and performance monitoring.

<br>

#### 2. You and two friends are the founders of a tech start-up. Your idea is a SaaS product enabling content creators to edit images and videos through a web application. You decided to host the platform on AWS since this is where you have the most expertise.
__Content creators will edit their footage directly on their devices (client-side), however, the footage must first be transcoded by the system in order to optimize storage and edit performance. The latency of the transcode operations is not critical, but users must be notified when their footage is ready to work. Additionally, premium users can choose to make their content available to certain people, which might be located anywhere on the globe, mostly to gather feedback. The platform also exposes a public API, enabling integration with other platforms.__
<br>__The backend is built with C++ and Node.js, it is designed to work with PostgreSQL, and the client application is built with Angular.__
<br>__Your goal is to reduce operational overhead as much as possible (due to the small team) and to optimize costs.__
<br><br>_Describe your solution below. Mention which AWS services you would choose, how they communicate with each other, and, equally important, why you have chosen a particular service. Be as explicit as possible._
<br>_Optionally, you can upload images to illustrate your design (feel free to use any drawing or diagram tool you wish; images don't have to be pretty)._
<br><br>

> We would like to propose the following solution:
> * __EC2__, for hosting our web application, this will allow us to scale our resources based on demand and also reduce costs by using reserved instances.
> * __S3__, to store our users' content, since it is a cost-effective, secure storage solution.
> * __CloudFront__, to serve content to our users around the world. It is fast and has advantages such as a global network and edge locations.
> * __Lambda__, a serverless on-demand solution that can manage our specific service of transcoding users' content. Costs are determined solely based on the duration of execution and the resources used, therefore minimal.
> * __SQS Queues__, to send messages to our users when their content is ready for work. It is a reliable, cost-effective notification system, and it does not require additional infrastructure on our side.
> * __API Gateway__, to expose our public API to other platforms. It is a fully-managed service, easily-maintainable, making it easy for developers to handle APIs at any scale. Pricing is calculated based solely on the API calls received and the amount of data transfered, therefore it is a cost-effective solution.
> * __RDS__, to manage our PostgreSQL database instances with less maintenance.
> * __Application Load Balancer__, to make the platform more efficient and provide a safety net in case of instance failure or downtime, redirecting traffic to available ones so that the service can remain available and not affect user experience.

> In the future, the afore-mentioned architecture can be adjusted/tuned for cost and speed efficiency, should the platform grow for greater needs.
